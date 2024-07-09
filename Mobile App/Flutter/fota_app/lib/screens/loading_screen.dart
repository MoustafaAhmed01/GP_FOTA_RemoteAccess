import 'package:animated_text_kit/animated_text_kit.dart';
import 'package:firebase_core/firebase_core.dart';
import 'package:flutter/material.dart';
import 'package:fota_app/screens/welcome_screen.dart';
import 'package:loading_animation_widget/loading_animation_widget.dart';

import '../constants/loading_screen_constants.dart';

class LoadingScreen extends StatefulWidget {
  /* Identifying the page */
  static String id = 'Screen_Loading';

  const LoadingScreen({super.key});
  /*---------------------------------------------*/
  @override
  State<LoadingScreen> createState() => _LoadingScreenState();
}

class _LoadingScreenState extends State<LoadingScreen> {

  Future<void> getFirebaseReady(BuildContext context) async {
    /* Initializing Firebase first */
    WidgetsFlutterBinding.ensureInitialized();
    await Firebase.initializeApp();
    /* ---------------------------------- */
    Navigator.pushReplacementNamed(context, WelcomeScreen.id);
  }

  @override
  void initState() {
    super.initState();
    /* Add Delay */

    Future.delayed(const Duration(seconds: 2), () {
      getFirebaseReady(context);
    });
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();

  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.black,
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.center,
        children: [
          Center(
            child: LoadingAnimationWidget.beat(
              color: const Color(0xff0a0ea1),
              size: 120,
            ),
          ),
          const SizedBox(
            height: 30,
          ),
          Padding(
            padding: const EdgeInsets.all(10.0),
            child: Row(
              children: [
                Flexible(
                  child: Hero(
                    tag: 'logo',
                    child: SizedBox(
                      height: 60,
                      child: Image.asset('images/FOTA_Logo.png'),
                    ),
                  ),
                ),
                const SizedBox(
                  width: 20,
                ),
                AnimatedTextKit(
                  animatedTexts: [
                    ColorizeAnimatedText(
                      'FOTA TEAM',
                      textStyle: const TextStyle(
                        fontWeight: FontWeight.w900,
                        fontSize: 50.0,
                        fontFamily: 'Horizon',
                      ),
                      speed: const Duration(milliseconds: 1000),
                      colors: colorizeColors,
                    ),
                  ],
                  isRepeatingAnimation: false,
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
