import 'package:flutter/material.dart';
import 'package:fota_app/screens/main/update/Update_Widgets/update_screen.dart';
import 'package:fota_app/screens/main/update/features/features_screen.dart';

import '../../../constants/update_screen_constants.dart';

class Firmware_Features_Screen extends StatefulWidget {
  static String id = 'Firmware_Features_Screen';

  const Firmware_Features_Screen({super.key});

  @override
  State<Firmware_Features_Screen> createState() =>
      _Firmware_Features_ScreenState();
}

class _Firmware_Features_ScreenState extends State<Firmware_Features_Screen> {
  @override
  Color _backgroundColor_1 = const Color(0xFF17171A);
  Color _backgroundColor_2 = const Color(0xFF17171A);
  void _handleTapDown_1(TapDownDetails details) {
    setState(() {
      // Change color when pressed
      _backgroundColor_1 = const Color(0xFF313136);
    });
  }

  void _handleTapUp_1(TapUpDetails details) {
    setState(() {
      // Change color back to original after release
      _backgroundColor_1 = const Color(0xFF17171A);
    });
  }

  void _handleTapDown_2(TapDownDetails details) {
    setState(() {
      // Change color when pressed
      _backgroundColor_2 = const Color(0xFF313136);
    });
  }

  void _handleTapUp_2(TapUpDetails details) {
    setState(() {
      // Change color back to original after release
      _backgroundColor_2 = const Color(0xFF17171A);
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.black,
      appBar: AppBar(
        backgroundColor: Colors.black,
        title: const Text(
          'Firmware and Features',
          style: TextStyle(
            color: Colors.white,
          ),
        ),
      ),
      body: SafeArea(
        child: Container(
          margin: const EdgeInsets.only(top: 10),
          child: Column(
            children: [
              Container(
                decoration: kUpdateContainerDecoration.copyWith(
                    borderRadius: kContainerOnly, color: _backgroundColor_1),
                child: GestureDetector(
                  onTapDown: _handleTapDown_1, // Call this when pressed
                  onTapUp: _handleTapUp_1, // Call this when released
                  onTap: () {
                    Navigator.pushNamed(context, ScreenUpdate.id);
                  },
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: [
                      const SizedBox(
                        height: 10,
                      ),
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 5),
                        child: const Text(
                          'Firmware update ',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 20,
                          ),
                        ),
                      ),
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 5),
                        child: const Text(
                            'Download and install your vehicle\'s firmware. Check your vehicle\'s current firmware version and update date',
                            style: kUpdateDetailsStyle),
                      ),
                      const SizedBox(
                        height: 15,
                      ),
                    ],
                  ),
                ),
              ),
              const SizedBox(
                height: 15,
              ),
              Container(
                decoration: kUpdateContainerDecoration.copyWith(
                    borderRadius: kContainerOnly, color: _backgroundColor_2),
                child: GestureDetector(
                  onTapDown: _handleTapDown_2, // Call this when pressed
                  onTapUp: _handleTapUp_2, // Call this when released
                  onTap: () {
                    Navigator.pushNamed(context, Features_Screen.id);
                  },
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: [
                      const SizedBox(
                        height: 10,
                      ),
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 5),
                        child: const Text(
                          'Features',
                          style: TextStyle(
                            color: Colors.white,
                            fontSize: 20,
                          ),
                        ),
                      ),
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 5),
                        child: const Text(
                            'Checkout all of your current features. Request a new feature to be integrated with your vehicle',
                            style: kUpdateDetailsStyle),
                      ),
                      const SizedBox(
                        height: 15,
                      ),
                    ],
                  ),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
