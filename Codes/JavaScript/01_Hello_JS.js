'use strict'
// Review Basic grammar

// Data Type
// number
123;
0.123;
1.2345e3;
NaN;
Infinity;
0x123;
0o123;

// string
"123";
`123`;
'123';
'I\'m \"OK\"!';
'\x41';
'\u4e2d\u6587';
`就相当于
Python里的
'''
<contents>
'''
啦
`
var lang = 'Python';
var version = '3.6';
var grammar = "f'string...{varname}string...'"
var formatString = `这个有点像${lang}${version}新添加的${grammar}特性`
var s = 'Hello';
s.toUpperCase();
s.toLowerCase();
s.indexOf('lo');
s.substring(0, 3);
s.substring(3); // 从3到结束

// boolearn
true;
2 > 1;

// Array
[1, 3, 11.23, 'Hello', null] // object

// object
var person = {
    name: "SigureMo",
    age: NaN,
    status: "hungry",
}
person.name;

var test = {
    name: '',
};

var out = formatString;

console.log(out);