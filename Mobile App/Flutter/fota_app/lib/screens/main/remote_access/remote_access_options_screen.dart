import 'package:flutter/material.dart';
import 'package:fota_app/components/rounded_button.dart';
import 'package:fota_app/screens/main/remote_access/ac_control/ac_control_screen.dart';
import 'package:fota_app/screens/main/remote_access/door_control/door_control_screen.dart';
import 'package:fota_app/screens/main/remote_access/speed/speed_control_screen.dart';

import 'engine/engine_control.dart';

class RemoteAccessOptions extends StatelessWidget {
  const RemoteAccessOptions({super.key});

  @override
  Widget build(BuildContext context) {
    return Container(
      width: double.infinity,
      padding: const EdgeInsets.all(20),
      decoration: const BoxDecoration(
        color: Colors.black54,
        borderRadius: BorderRadius.only(
          topRight: Radius.circular(30),
          topLeft: Radius.circular(30),
        ),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          const Text(
            'Options:',
            style: TextStyle(
              color: Colors.white70,
              fontSize: 30,
              letterSpacing: 2,
              fontWeight: FontWeight.w900,
            ),
          ),
          const SizedBox(
            height: 25,
          ),
          RoundedButton(
            title: ('Engine Control'),
            color: Colors.blueAccent,
            onPressed: () {
              Navigator.popAndPushNamed(context, EngineControl_Screen.id);
            },
            labelSize: 20,
          ),
          RoundedButton(
            title: 'Door Conrol',
            color: Colors.blueAccent,
            onPressed: () {
              Navigator.popAndPushNamed(context, DoorControlScreen.id);
            },
            labelSize: 20,
          ),
          RoundedButton(
            title: ('Speed Control'),
            color: Colors.blueAccent,
            onPressed: () {
              Navigator.popAndPushNamed(context, SpeedControlScreen.id);
            },
            labelSize: 20,
          ),
          RoundedButton(
            title: ('A/C'),
            color: Colors.blueAccent,
            onPressed: () {
              Navigator.popAndPushNamed(context, AirCondControlScreen.id);
            },
            labelSize: 20,
          ),
        ],
      ),
    );
  }
}
