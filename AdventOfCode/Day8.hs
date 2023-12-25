module Main where

import Text.Regex.Applicative (RE, (=~), asum, (<|>), string, sym, Alternative (many, some), psym)
import Data.Maybe (mapMaybe, fromJust)
import Data.Char (isLetter)
import qualified Data.Map.Strict as Map
import Control.Concurrent (threadDelay)
import Control.Monad (guard)

type Parser a = RE Char a

data Node = Node Char Char Char deriving (Eq, Show, Ord)
data Direction = L | R deriving(Eq, Show)
data Graph = Graph Node Node Node deriving (Eq, Show, Ord)
type GraphMap = Map.Map Node (Node, Node)
type Input = ([Graph], [Direction])

node :: RE Char Node
node = Node <$> letter <*> letter <*> letter
  where
    letter :: RE Char Char
    letter = head <$> some (psym isLetter)

graph :: Parser Graph
graph = Graph <$> (node <* string " = (") <*> (node <* string ", ") <*> (node <* sym ')')

genGraphMap :: [Graph] -> GraphMap
genGraphMap graphs = Map.fromList [(key, (value1, value2)) | Graph key value1 value2 <- graphs]
direction :: Parser [Direction]
direction = many $ asum [L <$ sym 'L', R <$ sym 'R']

 
prepare :: String -> Input
prepare s =
  let dirs = head (lines s)
  in (mapMaybe (=~ graph) (lines s), fromJust (dirs =~ direction))

navigate :: GraphMap -> Node -> [Direction] -> Int -> Int -> Int
navigate graphMap graphKey dirMap dirIndex acc
  | graphKey == Node 'Z' 'Z' 'Z' = acc
  | otherwise =
    case Map.lookup graphKey graphMap of
      Just (value1, value2) ->
        let currDir = dirMap !! dirIndex
            newGraphKey = if currDir == L then value1 else value2
            newDirIndex = (dirIndex + 1) `mod` length dirMap
        in navigate graphMap newGraphKey dirMap newDirIndex (acc + 1)
      Nothing -> acc

navigateGhost :: GraphMap -> [Direction] -> [Node] -> Int -> Int -> IO Int
navigateGhost graphMap dirMap graphKeys dirIndex acc = navigateGhost' graphKeys dirIndex acc
  where 
    navigateGhost' graphKeys dirIndex acc
       | all (\(Node _ _ c) -> c == 'Z') graphKeys = return acc 
       | otherwise = do
         print graphKeys
         guard $ filter (\ (Node _ _ c) -> c == 'Z') graphKeys == []
         -- threadDelay $ 10 ^ 5
         let currKeys = mapMaybe (`Map.lookup` graphMap) graphKeys
             updatedGraphKeys = map (\(value1, value2) ->
                                       if dirMap !! dirIndex == L then value1 else value2) currKeys
             newDirIndex = (dirIndex + 1) `mod` length dirMap
         navigateGhost' updatedGraphKeys newDirIndex (acc + 1)

example1 = "RL" ++ "\n\n" ++
           "AAA = (BBB, CCC)" ++ "\n" ++
           "BBB = (DDD, EEE)" ++ "\n" ++
           "CCC = (ZZZ, GGG)" ++ "\n" ++
           "DDD = (DDD, DDD)" ++ "\n" ++
           "EEE = (EEE, EEE)" ++ "\n" ++
           "GGG = (GGG, GGG)" ++ "\n" ++
           "ZZZ = (ZZZ, ZZZ)"

example2 = "LR" ++ "\n\n" ++ 
           "TTA = (TTB, XXX)" ++ "\n" ++
           "TTB = (XXX, TTZ)" ++ "\n" ++
           "TTZ = (TTB, XXX)" ++ "\n" ++
           "UUA = (UUB, XXX)" ++ "\n" ++
           "UUB = (UUC, UUC)" ++ "\n" ++
           "UUC = (UUZ, UUZ)" ++ "\n"++
           "UUZ = (UUB, UUB)" ++ "\n" ++
           "XXX = (XXX, XXX)"

main :: IO ()
main = do
  let (graphs, directions) = prepare example1
  inputFile <- readFile "./input.txt"
  let (graphs1, directions1) = prepare inputFile
  let (graphs2, directions2) = prepare example2
  -- print $ navigate (genGraphMap graphs) (Node 'A' 'A' 'A') directions 0 0
  -- print $ navigate (genGraphMap graphs1) (Node 'A' 'A' 'A') directions1 0 0
  -- print =<< navigateGhost (genGraphMap graphs2) directions2 [Node 'T' 'T' 'A', Node 'U' 'U' 'A'] 0 0
  -- return ()
  -- let initKeys = concatMap 
  --                (filter (\(Node _ _ c) -> c == 'A') . (\(Graph node1 node2 node3) -> 
  --                                                           [node1, node2, node3])) graphs1
  print =<< navigateGhost (genGraphMap graphs1) directions2 [Node 'A' 'A' 'A', Node 'U' 'U' 'A', Node 'D' 'V' 'A', Node 'V' 'X' 'A', Node 'J' 'H' 'A', Node 'N' 'M' 'A', Node 'P' 'X' 'A'] 0 0
  return ()
