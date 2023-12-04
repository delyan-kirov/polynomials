import * as fs from 'fs';

const filePath = './input.txt';
const input = fs.readFileSync(filePath, 'utf-8');

const example = 'Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green' + '\n' +
'Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue' + '\n' +
'Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red' + '\n' +
'Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red' + '\n' +
'Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green'

function parseInput(input: string): string[][][][] {
  function splitStringWithNumber(inputString: string): string[] {
      return inputString.split(/(\d+)/).map(item => item.trim()).filter(item => item !== '');
  }
  return input.split('\n')
    .map((line) => line.split(': '))
    .flat()
    .filter((str) => !str.includes('Game'))
    .map(line => line.split(';'))
    .map(list => list.map(item => item.split(',')))
    .map(list1 => list1.map(list2 => list2.map(str => splitStringWithNumber(str))));
}

function solution1(input : string[][][][]) : number {
  function isGamePossible(input: string[][][]): boolean {
    function isRoundPossible(input : string[][]): boolean{
      let red = 0; var blue = 0; var green = 0
      function switchHelper(pair : string []): void {
        switch(pair[1]) {
          case 'red'  : red   += parseInt(pair[0]); break;
          case 'green': green += parseInt(pair[0]); break;
          case 'blue' : blue  += parseInt(pair[0]); break;
         }
      }
      input.map(pair => switchHelper(pair))
      if (red > 12 || green > 13 || blue >14) { return false } else return true
  }
    return input.map(round => isRoundPossible(round))
                .reduce((acc, val) => acc && val)
  }
  let gameState : boolean[] = input.map(game => isGamePossible(game))
  var summa = 0
  for (let i = 0; i < gameState.length - 1; i++){
    let j = i + 1;
    if (gameState[i]) { summa = summa + j }
  }
  return summa
}

function solution2(input : string[][][][]) : number {
  function setPower(game: string[][][]) : number {
    var red = 0; var green = 0; var blue = 0
    function switchHelper (pair : string[]) : void{
      switch(pair[1]){
        case 'red'   : if (parseInt(pair[0]) > red)   { red = parseInt(pair[0])   }; break;
        case 'green' : if (parseInt(pair[0]) > green) { green = parseInt(pair[0]) }; break;
        case 'blue'  : if (parseInt(pair[0]) > blue)  { blue = parseInt(pair[0])  }; break;
        }
    }
    game.map(round => round.map(game => switchHelper(game)))
    return (red * green * blue)
  }
  return input.map(game => setPower(game))
              .reduce((acc, val) => acc + val)
}

var inputArray = parseInput(input)
// var inputArrayExample = parseInput(example)
console.log(`The solution for problem one is: ${solution1(inputArray)}`)
console.log(`The solution for problem two is: ${solution2(inputArray)}`)


