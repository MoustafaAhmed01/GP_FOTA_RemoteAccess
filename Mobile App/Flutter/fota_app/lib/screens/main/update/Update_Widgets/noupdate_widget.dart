import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';

import '../../../../components/alerts.dart';
import '../../../../constants/update_screen_constants.dart';
import 'update_screen.dart';

Widget NoUpdateContainer() {
  if (g_CurrentUpdateState == false) {
    if (g_UpdateFound == true) {
      Fluttertoast.cancel();
      toastFun('New Update Found, Refresh!');
    } else {
      print('Entered No update');
      Fluttertoast.cancel();
      toastFun('Up to date');
    }
  }

  return Container(
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Container(
          margin: const EdgeInsets.only(left: 15),
          child: const Text(
            'Your firmware is up to date.',
            style: TextStyle(
              fontWeight: FontWeight.w600,
              fontSize: 20,
              color: Colors.white,
            ),
          ),
        ),
        const SizedBox(
          height: 10,
        ),
        Container(
          height: 100,
          decoration: kUpdateContainerDecoration,
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              Container(
                margin: const EdgeInsets.only(left: 15, top: 10),
                child: const Text(
                  'Current firmware information',
                  style: kUpdateDetailsTitleStyle,
                ),
              ),
              const SizedBox(
                height: 5,
              ),
              Container(
                margin: const EdgeInsets.only(left: 15, top: 5),
                child: Text(
                  '• Version: $g_CurrentSoftwareVersion',
                  style: kUpdateDetailsStyle,
                ),
              ),
              Container(
                margin: const EdgeInsets.only(left: 15, top: 5),
                child: Text(
                  '• Updated on: $g_CurrentSoftwareDate',
                  style: kUpdateDetailsStyle,
                ),
              ),
            ],
          ),
        )
      ],
    ),
  );
}
