{-# LANGUAGE MultiWayIf #-}

module Main where

import Data.List (maximumBy, sort, sortBy)
import Data.List.NonEmpty (nonEmpty)
import qualified Data.Map as Map
import qualified Data.Set as Set
import Data.Tree (flatten)

data Card
  = A
  | K
  | J
  | Q
  | T
  | One
  | Two
  | Three
  | Four
  | Five
  | Six
  | Seven
  | Eight
  | Nine
  deriving (Show, Eq)

example =
  "32T3K 765"
    ++ "\n"
    ++ "T55J5 684"
    ++ "\n"
    ++ "KK677 28"
    ++ "\n"
    ++ "KTJJT 220"
    ++ "\n"
    ++ "QQQJA 483"

parseInput :: String -> [(Hand, Int)]
parseInput input =
  [(strToHand hand, read bet) | line <- lines input, let (hand : bet : _) = words line]
 where
  strToHand :: String -> Hand
  strToHand s =
    Hand
      (chrToCard $ head s)
      (chrToCard $ s !! 1)
      (chrToCard $ s !! 2)
      (chrToCard $ s !! 3)
      (chrToCard $ s !! 4)
  chrToCard :: Char -> Card
  chrToCard 'T' = T
  chrToCard 'A' = A
  chrToCard 'K' = K
  chrToCard 'J' = J
  chrToCard 'Q' = Q
  chrToCard '1' = One
  chrToCard '2' = Two
  chrToCard '3' = Three
  chrToCard '4' = Four
  chrToCard '5' = Five
  chrToCard '6' = Six
  chrToCard '7' = Seven
  chrToCard '8' = Eight
  chrToCard '9' = Nine
  chrToCard x = error $ "Invalid card character " ++ [x]

cardValue :: Card -> Int
cardValue A = 14
cardValue K = 13
cardValue Q = 12
cardValue J = 11
cardValue T = 10
cardValue One = 1
cardValue Two = 2
cardValue Three = 3
cardValue Four = 4
cardValue Five = 5
cardValue Six = 6
cardValue Seven = 7
cardValue Eight = 8
cardValue Nine = 9

cardValue' :: Card -> Int
cardValue' J = 0 
cardValue' card = cardValue card

compareCards :: [Card] -> [Card] -> Ordering
compareCards xs ys = compareLists compareCards' xs ys
  where
    compareCards' :: Card -> Card -> Ordering
    compareCards' card1 card2 = compare (cardValue' card1) (cardValue' card2)
    -- extend compare cards to lists 
    compareLists :: (a -> a -> Ordering) -> [a] -> [a] -> Ordering
    compareLists _ [] [] = EQ
    compareLists _ [] _  = LT
    compareLists _ _ []  = GT
    compareLists cmp (x:xs) (y:ys) =
      case cmp x y of
        EQ -> compareLists cmp xs ys
        result -> result

instance Ord Card where
  compare card1 card2 = compare (cardValue card1) (cardValue card2)

data Hand = Hand Card Card Card Card Card
  deriving (Show, Eq)

instance Ord Hand where
  compare hand1 hand2
    | cardType hand1 > cardType hand2 = GT
    | cardType hand1 < cardType hand2 = LT
    | otherwise = compare (handToList hand1) (handToList hand2)
   where
    handToList (Hand a1 a2 a3 a4 a5) = [a1, a2, a3, a4, a5]
    cardType :: Hand -> Int
    cardType hand
      | fiveKind hand = 6
      | fourKind hand = 5
      | fullHouse hand = 4
      | threeKind hand = 3
      | twoPair hand = 2
      | onePair hand = 1
      | highCard hand = 0

compareHand :: Hand -> Hand -> Ordering
compareHand hand1 hand2
  | cardType hand1 > cardType hand2 = GT
  | cardType hand1 < cardType hand2 = LT
  | otherwise = compareCards (handToList hand1) (handToList hand2)
 where
  handToList (Hand a1 a2 a3 a4 a5) = [a1, a2, a3, a4, a5]
  cardType :: Hand -> Int
  cardType hand
    | fiveKind $ joke hand = 6
    | fourKind $ joke hand = 5
    | fullHouse $ joke hand = 4
    | threeKind $ joke hand = 3
    | twoPair $ joke hand = 2
    | onePair $ joke hand = 1
    | highCard $ joke hand = 0

fourKind :: Hand -> Bool
fourKind (Hand a1 a2 a3 a4 a5) = do
  let deck = [a1, a2, a3, a4, a5]
      multiSet = Map.fromListWith (+) [(el, 1) | el <- deck]
      maxMult = maximum $ [t | (s, t) <- Map.assocs multiSet]
  maxMult == 4

joke :: Hand -> Hand
joke (Hand J J J J J) = Hand J J J J J
joke (Hand a1 a2 a3 a4 a5) = do
  let handList = [a1, a2, a3, a4, a5]
      multiSet = Map.fromListWith (+) [(el, 1) | el <- handList]
      nonJs = Map.assocs $ Map.delete J multiSet
      h = let maxNonJ =
                fst $
                maximumBy (\(_, x) (_, y) -> compare x y) $
                Map.assocs $
                Map.delete J multiSet
          in (\x -> if x == J then maxNonJ else x) <$> handList
  case h of [a1, a2, a3, a4, a5] -> Hand a1 a2 a3 a4 a5

fiveKind :: Hand -> Bool
fiveKind (Hand a1 a2 a3 a4 a5) = do
  let deck = [a1, a2, a3, a4, a5]
  let thisHand = Set.fromList deck
  Set.size thisHand == 1

fullHouse :: Hand -> Bool
fullHouse (Hand a1 a2 a3 a4 a5) = do
  let deck = [a1, a2, a3, a4, a5]
  let thisHand = Set.fromList deck
  Set.size thisHand == 2 && not (fourKind $ Hand a1 a2 a3 a4 a5)

twoPair :: Hand -> Bool
twoPair (Hand a1 a2 a3 a4 a5) = do
  let deck = [a1, a2, a3, a4, a5]
  let thisHand = Set.fromList deck
  Set.size thisHand == 3

onePair :: Hand -> Bool
onePair (Hand a1 a2 a3 a4 a5) = do
  let deck = [a1, a2, a3, a4, a5]
  let thisHand = Set.fromList deck
  Set.size thisHand == 4

threeKind :: Hand -> Bool
threeKind (Hand a1 a2 a3 a4 a5) = do
  let handList = [a1, a2, a3, a4, a5]
      multiSet = Map.fromListWith (+) [(el, 1) | el <- handList]
      multiSetSize = length multiSet
  multiSetSize == 3 && maximum (Map.elems multiSet) == 3

highCard :: Hand -> Bool
highCard (Hand a1 a2 a3 a4 a5) = do
  let deck = [a1, a2, a3, a4, a5]
  let thisHand = Set.fromList deck
  Set.size thisHand == 5

solution_1 :: String -> Int
solution_1 s = do
  let hand_bet_s = sortBy (\ (x, _) (y, _) -> compare y x) $ parseInput s
      bets = reverse [t | (s, t) <- hand_bet_s]
  sum $ zipWith (*) bets [1 .. length bets]

solution_2 :: String -> Int
solution_2 s = do
  let hand_bet_s = sortBy (\(x, _) (y, _) -> compareHand x y) $ parseInput s
      bets = [t | (s, t) <- hand_bet_s]
  sum $ zipWith (*) bets [1 .. length bets]

main :: IO ()
main = do
  inputFile <- readFile "./input.txt"
  print $ solution_1 inputFile
  print $ solution_1 example
  print $ solution_2 inputFile
  print $ solution_2 example
