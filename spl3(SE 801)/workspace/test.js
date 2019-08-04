"use strict";
// let defaults = { food: "spicy", price: "$$", ambiance: "noisy" };
// let search = { food: "rich", ...defaults };
exports.__esModule = true;
// let obj = {
//     a:100,
//     b:"second atribute",
//     f:function(x){
//         console.log('value:'+x);
//     }
// };
// console.log(typeof(obj));
//////////////////////////////////////////
// interface LabeledValue {
//     label: string;
// }
// function printLabel(labeledObj: LabeledValue) {
//     console.log(labeledObj.label);
// }
// let myObj = {size: 10, label: "Size 10 Object"};
// printLabel(myObj);
/////////////////////////////////////////
// class Control {
//     private state: any;
// }
// interface SelectableControl extends Control {
//     select(): void;
// }
// class Button extends Control implements SelectableControl {
//     select() { }
// }
// class TextBox extends Control {
//     select() { }
// }
// //new Button().
// // Error: Property 'state' is missing in type 'Image'.
// class Image2 implements SelectableControl {
//     //private state: any;
//     select() { }
// }
// class Location {
// }
////////////////////////////////////////////////
// enum FileAccess {
//     // constant members
//     None,
//     Read    = 1 << 1,
//     Write   = 1 << 2,
//     ReadWrite  = Read | Write,
//     // computed member
//     G = "123".length
// }
// console.log(FileAccess.None);
// console.log(FileAccess.Read);
// console.log(FileAccess.ReadWrite);
// console.log(FileAccess.Write);
// console.log(FileAccess.G);
//////////////////////////////////////////
// enum Direction {
//     Up = "UP",
//     Down = "DOWN",
//     Left = "LEFT",
//     Right = "RIGHT",
//     Num = 34,
// }
// console.log(Direction.Num);
///////////////////////////////////////////
// enum E1 { X, Y, Z }
// enum E2 {
//     A = 1, B, C
// }
// console.log(E2.B);
//////////////////////////////////////////
// var ZipCodeValidator_1 = require("./ZipCodeValidator");
// // Some samples to try
// var strings = ["Hello", "98052", "101"];
// // Validators to use
// var validator = new ZipCodeValidator_1.ZipCodeValidator();
// // Show whether each string passed each validator
// strings.forEach(function (s) {
//     console.log("\"" + s + "\" - " + (validator.isAcceptable(s) ? "matches" : "does not match"));
// });

class Hero {
    constructor(name, level) {
        this.name = name;
        this.level = level;
        console.log('in constructor');
    }
    test(){
        console.log('tested');
    }
}

let t = new Hero("tulshi","testing");
t.test();