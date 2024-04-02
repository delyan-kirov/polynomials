// Task 1: Build a function-based console log message generator
function consoleStyler() {
    function consoleStyler(color, background, fontSize, txt) {
    var message = "%c" + txt;
    var style = `color: ${color};`;
    style += `background: ${background};`;
    style += `font-size: ${fontSize};`;
    console.log(message, style);
}
}

// Task 2: Build another console log message generator
function celebrateStyler() {
        var fontStyle = "color: tomato; font-size: 50px;";

    if (reason === "birthday") {
        console.log(`%cHappy birthday`, fontStyle);
    } else if (reason === "champions") {
        console.log(`%cCongrats on the title!`, fontStyle);
    } else {
        console.log("Celebrate your reason in style!");
    }
}

// Task 3: Run both the consoleStyler and the celebrateStyler functions

// Invoking consoleStyler function
consoleStyler('#1d5c63', '#ede6db', '40px', 'Congrats!');

// Invoking celebrateStyler function
celebrateStyler('birthday');

// Task 4: Insert a congratulatory and custom message
function styleAndCelebrate() {
    consoleStyler(color, background, fontSize, txt);
    celebrateStyler(reason);
}

// Example usage:
styleAndCelebrate('ef7c8e', 'fae8e0', '30px', 'You made it!', 'champions');

// Call styleAndCelebrate
