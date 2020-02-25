-- |
-- Module      :  MakeChange
-- Description :  Calculate the denominations required for change
-- Copyright   :  Copyright Alexander DuPree (c) 2020
-- Maintainer  :  Alexander DuPree
-- Stability   :  experimental
-- Portability :  POSIX

module MakeChange
  ( Money
  )
where

import Data.List
import Data.Function

data Money = Dollar | Quarter | Dime | Nickel | Penny 
  deriving(Show, Eq)

value :: Money -> Int
value Dollar  = 100
value Quarter = 25
value Dime    = 10
value Nickel  = 5
value Penny   = 1

coins = [100, 25, 10, 5, 1]

makeChange :: Int -> [Money]
makeChange 100 = [Dollar]
makeChange 25  = [Quarter]
makeChange 10  = [Dime]
makeChange 5   = [Nickel]
makeChange 1   = [Penny]
makeChange 0   = []

makeChange change = minimumBy (compare `on` length) makeChange'
  where makeChange' = map makeChange (map (change -) coins)
