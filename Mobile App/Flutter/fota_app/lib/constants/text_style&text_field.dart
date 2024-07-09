import 'package:flutter/material.dart';

/*Text Style*/
const kTextstyle4_white = TextStyle(
  color: Colors.white,
  fontSize: 17,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);
const kTextstyle_white = TextStyle(
  color: Colors.white,
  fontSize: 20,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);
const kTextstyle_black = TextStyle(
  color: Colors.black,
  fontSize: 20,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);
const kTextstyle2_black = TextStyle(
  color: Colors.black,
  fontSize: 23,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);
const kTextstyle2_white = TextStyle(
  color: Colors.white,
  fontSize: 23,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);
const kTextstyle3_black = TextStyle(
  color: Colors.black,
  fontSize: 30,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);
const kTextstyle3_white = TextStyle(
  color: Colors.white,
  fontSize: 30,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);

const kTextstyle3_white12 = TextStyle(
  color: Colors.white12,
  fontSize: 30,
  //fontFamily: 'Satisfy',
  fontWeight: FontWeight.bold,
  //letterSpacing: 2.5,
);

const kTextFieldDecoration = InputDecoration(
  labelStyle: kTextstyle_white,
  hintStyle: kTextstyle_white,
  filled: true,
  fillColor: Colors.black26,
  contentPadding: EdgeInsets.symmetric(vertical: 10.0, horizontal: 20.0),
  border: OutlineInputBorder(
    borderRadius: BorderRadius.all(Radius.circular(32.0)),
  ),
  enabledBorder: OutlineInputBorder(
    borderSide: BorderSide(color: Colors.blue, width: 2.0),
    borderRadius: BorderRadius.all(Radius.circular(32.0)),
  ),
  focusedBorder: OutlineInputBorder(
    borderSide: BorderSide(color: Colors.blue, width: 2.0),
    borderRadius: BorderRadius.all(Radius.circular(32.0)),
  ),
);
