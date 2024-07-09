import 'package:flutter/material.dart';

class lock_unlock extends StatelessWidget {

  const lock_unlock({super.key, required this.colour, required this. child});

    final Color colour;
    final Widget child;

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.all(15.0) ,
      padding: const EdgeInsets.all(20.0),
      decoration: BoxDecoration(
        color: colour,
        borderRadius: BorderRadius.circular(50),
      ),
      child:child,

    );
  }
}
