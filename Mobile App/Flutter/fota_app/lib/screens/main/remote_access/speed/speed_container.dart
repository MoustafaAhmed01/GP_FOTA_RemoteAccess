import 'package:flutter/material.dart';

class Speed_container extends StatelessWidget {
  const Speed_container({super.key, required this.colour, required this.child});

  final Color colour;
  final Widget child;

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.only(top: 10.0, left: 6, right: 6),
      padding: const EdgeInsets.all(5.0),
      height: 40,
      width: 100,
      decoration: BoxDecoration(
        color: colour,
        borderRadius: BorderRadius.circular(50),
      ),
      child: child,
    );
  }
}
