import 'package:flutter/material.dart';

/*---------------------------------------*/
/* Colors */

/* Styles */

const kUpdateTitleStyle = TextStyle(
  fontWeight: FontWeight.w600,
  fontSize: 20,
  color: Colors.white,
);

const kUpdateDetailsTitleStyle = TextStyle(
  fontWeight: FontWeight.w700,
  fontSize: 12,
  color: Color(0xffE5E5E5),
);

/*--------*/
const kUpdateDetailsStyle = TextStyle(
  fontWeight: FontWeight.w400,
  fontSize: 13,
  color: Color(0xffB7B7BB),
);
/*--------*/
BoxDecoration kUpdateContainerDecoration = BoxDecoration(
  color: const Color(0xFF17171A),
  borderRadius: BorderRadius.circular(25),
);
/*--------*/
BorderRadius kImageWithContainerBorders = const BorderRadius.only(
  topLeft: Radius.circular(1000), // Set a large value for the top left corner
  topRight:
      Radius.circular(20), // Set the desired value for the top right corner
  bottomLeft:
      Radius.circular(0), // Set 0 for the bottom left corner to make it square
  bottomRight:
      Radius.circular(0), // Set 0 for the bottom right corner to make it square
);
/*-------*/
BorderRadius kImageContainer = const BorderRadius.only(
  topLeft: Radius.circular(0), // Set a large value for the top left corner
  topRight:
      Radius.circular(0), // Set the desired value for the top right corner
  bottomLeft:
      Radius.circular(25), // Set 0 for the bottom left corner to make it square
  bottomRight: Radius.circular(
      25), // Set 0 for the bottom right corner to make it square
);

BorderRadius kContainerOnly = const BorderRadius.only(
  topLeft: Radius.circular(25), // Set a large value for the top left corner
  topRight:
      Radius.circular(25), // Set the desired value for the top right corner
  bottomLeft:
      Radius.circular(25), // Set 0 for the bottom left corner to make it square
  bottomRight: Radius.circular(
      25), // Set 0 for the bottom right corner to make it square
);
/*---------------------------------------*/
