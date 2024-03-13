{-# LANGUAGE DisambiguateRecordFields #-}
{-# LANGUAGE DuplicateRecordFields #-}
{-# LANGUAGE MonadComprehensions #-}
{-# LANGUAGE MultiWayIf #-}
{-# LANGUAGE OverloadedRecordDot #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE QuasiQuotes #-}
{-# LANGUAGE ScopedTypeVariables #-}

module Main where

import Control.Applicative
import Data.Text (Text)
import Data.Text qualified as T
import Database.SQLite.Simple
import Database.SQLite.Simple.FromRow
import Database.SQLite.Simple.QQ (sql)

data TestField = TestField Int Text deriving (Show)

instance FromRow TestField where
  fromRow = TestField <$> field <*> field

instance ToRow TestField where
  toRow (TestField id_ str) = toRow (id_, str)

data Person = Person
  { firstName :: Text
  , lastName :: Text
  , id :: Int
  , age :: Int
  }
  deriving (Show, Eq)

instance FromRow Person where
  fromRow = Person <$> field <*> field <*> field <*> field

instance ToRow Person where
  toRow person =
    toRow
      ( person.firstName
      , person.lastName
      , person.id
      , person.age
      )

main :: IO ()
main = do
  conn <- open "test.db"
  execute_ conn [sql|
   CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, strTEXT)
  |]

  execute conn [sql|
    INSERT INTO test (str) VALUES (?)
  |] (Only ("test string 2" :: String))

  execute conn [sql|
    INSERT INTO test (id, str) VALUES (?,?)
  |] (TestField 13 "test string 3")

  rowId <- lastInsertRowId conn
  executeNamed
    conn
    "UPDATE test SET str = :str WHERE id = :id"
    [":str" := ("updated str" :: T.Text), ":id" := rowId]

  r :: [TestField] <- query_ conn "SELECT * from test" :: IO [TestField]
  mapM_ print r
  print $ length r
  execute conn "DELETE FROM test WHERE id = ?" (Only rowId)
  close conn

-- LINKS
--
-- postgres sum types [[https://dev.to/monacoremo/sum-types-in-relational-databases-yet-another-imo-pretty-neat-way-to-model-them-in-sql-3o3a]]
--
-- bingdings for sqlite3 [[https://hackage.haskell.org/package/sqlite-simple]]
