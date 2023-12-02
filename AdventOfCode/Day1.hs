module Main where

import Data.List (isPrefixOf, isSuffixOf, find, lines)

example = "1abc2\npqr3stu8vwx\na1b2c3d4e5f\ntreb7uchet"
example' = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen"

digits = ["1", "2", "3", "4", "5", "6", "7", "8", "9"] ++
         ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]

findDigits :: String -> Int
findDigits s =
  let t = filter (`elem` digits) s
  in case length t of
    1 -> let t' = read [head t] in 11 * t'
    0 -> 0
    _ -> let [t', t''] = map (\x -> read [x]) (head t : [last t]) in 10 * t' + t''
    where
      digits = "1234567890"

findDigsPre :: String -> Int
findDigsPre (x:xs) = do
  let digitPrefix = findPrefix (x:xs) digits
  case digitPrefix of
    Nothing -> findDigsPre xs
    Just s  -> digitsToInt s :: Int
  where
  findPrefix :: String -> [String] -> Maybe String
  findPrefix str = find (`isPrefixOf` str)

findDigsPost :: String -> Int
findDigsPost str = do
  let digitPostfix = findPostfix str digits
  case digitPostfix of
    Nothing -> findDigsPost (init str)  -- Remove the last character and try again
    Just s  -> digitsToInt s :: Int
  where
    findPostfix :: String -> [String] -> Maybe String
    findPostfix str = find (`isSuffixOf` str)

digitsToInt :: String -> Int
digitsToInt s = case s of
  "one"   -> 1; "two"   -> 2
  "three" -> 3; "four"  -> 4
  "five"  -> 5; "six"   -> 6
  "seven" -> 7; "eight" -> 8
  "nine"  -> 9; "1"     -> 1
  "2"     -> 2; "3"     -> 3
  "4"     -> 4; "5"     -> 5
  "6"     -> 6; "7"     -> 7
  "8"     -> 8; "9"     -> 9
  _ -> 10

solution :: String -> Int
solution s = sum $ map findDigits (lines s)

solution' :: String -> Int
solution' s = do
  let s' = lines s :: [String]
      t1 = map ((*10) . findDigsPre) s'
      t2 = map findDigsPost s'
  sum $ zipWith (+) t1 t2

main :: IO ()
main = do
  input <- readFile "./input.txt"
  putStrLn ""
  putStrLn $ "The solution for the easier problem is: " ++ show (solution input)
  putStrLn $ "The solution for the harder problem is: " ++ show (solution' input)








