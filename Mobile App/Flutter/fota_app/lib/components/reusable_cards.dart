import 'package:flutter/material.dart';

class longCard extends StatelessWidget {
  const longCard(
    this.colour, [
    this.cardChild,
    this.onPress,
    this.imageDisplay,
  ]);
  final Color colour;
  final Widget? cardChild;
  final String? imageDisplay;
  final Function()? onPress;

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: onPress,
      child: Container(
        margin: const EdgeInsets.all(10),
        width: double.infinity,
        height: 120,
        decoration: BoxDecoration(
          color: colour,
          image: DecorationImage(
            image: AssetImage('$imageDisplay'),
            fit: BoxFit.cover,
          ),
          borderRadius: BorderRadius.circular(30),
        ),
        child: cardChild,
      ),
    );
  }
}

class thinCard extends StatelessWidget {
  const thinCard(
    this.colour, [
    this.cardChild,
    this.onPress,
    this.imageDisplay,
  ]);
  final Color colour;
  final Widget? cardChild;
  final Function()? onPress;
  final String? imageDisplay;

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: onPress,
      child: Container(
        margin: const EdgeInsets.all(10),
        width: double.infinity,
        height: 200,
        decoration: BoxDecoration(
          color: colour,
          image: DecorationImage(
            image: AssetImage('$imageDisplay'),
            fit: BoxFit.cover,
          ),
          borderRadius: BorderRadius.circular(30),
        ),
        child: cardChild,
      ),
    );
  }
}
