module Main where

import qualified Data.Map as Map
import qualified Data.Set as Set
import Data.Tree (flatten)
import Data.List (sort, sortBy)

data Card
  = A
  | K
  | Q
  | J
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
  deriving (Show, Eq, Ord)

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

removeAt _ [] = []
removeAt n xs
  | n < 0 = xs -- Index is negative, do nothing
  | n >= length xs = xs -- Index is out of bounds, do nothing
  | otherwise = before ++ after
 where
  (before, _ : after) = splitAt n xs

cardType :: Hand -> Int
cardType hand
 | fiveKind hand = 6
 | fourKind hand = 5
 | fullHouse hand = 4
 | threeKind hand = 3
 | twoPair hand = 2
 | onePair hand = 1
 | highCard hand = 0

allSame :: (Eq a) => [a] -> Bool
allSame [] = True
allSame (x : xs) = all (== x) xs

fourKind :: Hand -> Bool
fourKind (Hand a1 a2 a3 a4 a5) = do
  let deck = [a1, a2, a3, a4, a5]
  (not . allSame) deck && any allSame (subsets deck)

subsets :: [a] -> [[a]]
subsets [] = [[]]
subsets xs = subsets' [[]] 0 xs
 where
  subsets' :: [[a]] -> Int -> [a] -> [[a]]
  subsets' carry len xs
    | len == 0 = subsets' [removeAt len xs] (len + 1) xs
    | len == length xs = carry
    | otherwise = subsets' (removeAt len xs : carry) (len + 1) xs

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
  let res = sum $ zipWith (*) bets [1 .. length bets]
  res
  
main :: IO ()
main = do
  inputFile <- readFile "./input.txt"
  print $ solution_1 inputFile
  print $ solution_1 example
