import * as fs from "fs";

const filePath = "./input.txt";
const input = fs.readFileSync(filePath, "utf-8");

const example = "Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53" + "\n" +
  "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19" + "\n" +
  "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1" + "\n" +
  "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83" + "\n" +
  "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36" + "\n" +
  "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11";

function parseData(s: string): number {
  const s1 = s.split(": ")[1].split(" | ")
    .map((t) =>
      t.split(" ")
        .filter((p) => p.length !== 0).map((q) => Number(q))
    );
  const winningCards: number[] = s1[0];
  const ownedCards: number[] = s1[1];
  return Math.floor(
    2 ** (ownedCards.filter((s) => winningCards.includes(s)).length - 1),
  );
}

function parseData1(s: string): number {
  const s1 = s.split(": ")[1].split(" | ")
    .map((t) =>
      t.split(" ")
        .filter((p) => p.length !== 0).map((q) => Number(q))
    );
  const winningCards: number[] = s1[0];
  const ownedCards: number[] = s1[1];
  return ownedCards.filter((s) => winningCards.includes(s)).length;
}

function solution(inputStr: string): number {
  return inputStr
    .split("\n")
    .filter((x) => x.length !== 0)
    .map((s) => parseData(s))
    .reduce((acc, val) => acc + val);
}

function solution1(inputStr: string): number {
  const initArray = inputStr.split("\n").filter((x) => x.length !== 0).map(
    (x) => parseData1(x)
  );
  var instances = Array(initArray.length).fill(1);
  for (let i = 0; i <= initArray.length; i++) {
    for (let j = i + 1; j <= i + initArray[i]; j++) {
      instances[j] = instances[j] + instances[i];
    }
  }
  return instances.reduce((acc, val) => acc + val);
}

console.log(`The solution for part 1 example is: ${solution(example)}`);
console.log(`The solution for part 2 example is: ${solution1(example)}`);
console.log(`The solution for part 1 input   is: ${solution(input)}`);
console.log(`The solution for part 2 input   is: ${solution1(input)}`);
