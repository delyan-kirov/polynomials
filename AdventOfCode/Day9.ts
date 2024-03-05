import * as fs from "fs";

const filePath = "./input.txt";
const input = fs.readFileSync(filePath, "utf-8");

// Tests: 
// const example = [0, 3, 6, 9, 12, 15];
// const example1 = [1, 3, 6, 10, 15, 21];
// const example2 = [10, 13, 16, 21, 30, 45]
//
// const inputStr = "0 3 6 9 12 15" + "\n" +
//                  "1 3 6 10 15 21" + "\n" +
//                  "10 13 16 21 30 45"

function findDiff(nums: number[]): number {
  var output: number[][] = [nums]; // Change this line

  while (nums.some((num) => num !== 0)) {
    var currArray: number[] = [];
    for (let i = 1; i < nums.length; i++) {
      currArray.push(nums[i] - nums[i - 1]);
    }

    output.push(currArray);
    nums = currArray; 
  }
  return output.map((subArray) => subArray.slice(-1)[0])
                                          .reduce((elem, acc) => elem + acc, 0);
}

function findBack(nums: number[]): number {
  var output: number[][] = [nums];

  while (nums.some((num) => num !== 0)) {
    var currArray: number[] = [];
    for (let i = 1; i < nums.length; i++) {
      currArray.push(nums[i] - nums[i - 1]);
    }
    output.push(currArray);
    nums = currArray;
  }
  var diffs: number[] = output.map(subArray => subArray.slice(0)[0]).reverse()
  var zeros: number[] = Array(diffs.length).fill(0)
  for (let i = 1; i <= diffs.length; i++) {
    zeros[i] = diffs[i - 1] - zeros[i - 1]
  }
  return (zeros.slice(-1)[0]);
}

function parseArrays(input: string): number[][] {
  const lines = input.trim().split('\n');
  return lines.map(line => line.split(' ').map(Number));
}

// Results:
console.log(parseArrays(input).map(x => findDiff(x)).reduce((elem, acc) => elem + acc))
console.log(parseArrays(input).map(x => findBack(x)).reduce((elem, acc) => elem + acc))
