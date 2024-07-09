import 'package:animated_text_kit/animated_text_kit.dart';
import 'package:flutter/material.dart';
import 'package:loading_animation_widget/loading_animation_widget.dart';

import '../../../../constants/loading_screen_constants.dart';
import 'location_screen.dart';

Widget LocationLoadingScreen(BuildContext context) {
  Future.delayed(const Duration(milliseconds: 10000), () {
    // Pop the screen after 5 seconds
    if (g_LocationScreenReady == false) {
      Navigator.of(context).pop();
      showDialog(
        context: context,
        builder: (BuildContext context) {
          return AlertDialog(
            elevation: 40,
            title: const Text(
              'Connection Timeout',
              style: TextStyle(
                color: Colors.white,
              ),
            ),
            content: const Text(
              'Your internet connection is bad.\nPlease try again later!',
              style: TextStyle(
                color: Colors.white70,
              ),
            ),
            actions: [
              Center(
                child: SizedBox(
                  width: 120,
                  height: 40,
                  child: TextButton(
                    style: const ButtonStyle(
                      shape: WidgetStatePropertyAll(
                        RoundedRectangleBorder(
                          borderRadius: BorderRadius.only(
                            topLeft: Radius.circular(20),
                            bottomRight: Radius.circular(20),
                            topRight: Radius.circular(20),
                            bottomLeft: Radius.circular(20),
                          ),
                        ),
                      ),
                      elevation: WidgetStatePropertyAll(10),
                      backgroundColor: WidgetStatePropertyAll(Colors.white12),
                    ),
                    onPressed: () =>
                        Navigator.of(context).pop(), // Dismiss the dialog
                    child: const Text(
                      'Ok',
                      style:
                          TextStyle(fontSize: 15, fontWeight: FontWeight.w500),
                    ),
                  ),
                ),
              ),
            ],
          );
        },
      );
    }
  });

  return Container(
    decoration: const BoxDecoration(color: Colors.black),
    child: Column(
      children: [
        const SizedBox(
          height: 40,
        ),
        Center(
          child: LoadingAnimationWidget.hexagonDots(
            color: const Color(0xff0a0ea1),
            size: 120,
          ),
        ),
        const SizedBox(
          height: 30,
        ),
        const SizedBox(
          height: 10,
        ),
        AnimatedTextKit(
          animatedTexts: [
            ColorizeAnimatedText(
              'Getting Ready',
              textStyle: const TextStyle(
                fontWeight: FontWeight.w900,
                fontSize: 40.0,
                fontFamily: 'Horizon',
              ),
              speed: const Duration(milliseconds: 1000),
              colors: colorizeColors,
            ),
          ],
          isRepeatingAnimation: true,
        ),
        AnimatedTextKit(
          animatedTexts: [
            ColorizeAnimatedText(
              'Please wait..',
              textStyle: const TextStyle(
                fontWeight: FontWeight.w300,
                fontSize: 20.0,
                fontFamily: 'Horizon',
              ),
              speed: const Duration(milliseconds: 1000),
              colors: colorizeColors,
            ),
          ],
          isRepeatingAnimation: true,
        ),
      ],
    ),
  );
}
