import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:loading_animation_widget/loading_animation_widget.dart';

import '../../../../components/alerts.dart';
import '../../../../constants/update_screen_constants.dart';
import 'update_screen.dart';

Widget PendingInstallationContainer() {
  /* Converting the string to int */
  int installationPercentage = int.tryParse(g_ESPInstallPercentage) ?? 0;

  /* Handling the toast */
  if (g_CurrentUpdateState == false) {
    if (g_InstallStart == false) {
      Fluttertoast.cancel();
      toastFun('Pending Installation!');
    } else if (g_InstallStart == true) {
      if (installationPercentage >= 1) {
      } else {
        Fluttertoast.cancel();
        toastFun('Installing');
      }
    }
  }

  return Column(
    crossAxisAlignment: CrossAxisAlignment.start,
    children: [
      Container(
        margin: const EdgeInsets.only(left: 15),
        child: const Text(
          'Pending Install',
          style: TextStyle(
            fontWeight: FontWeight.w600,
            fontSize: 20,
            color: Colors.white,
          ),
        ),
      ),
      const SizedBox(
        height: 20,
      ),
      const SizedBox(
        height: 5,
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
      ),
      const SizedBox(
        height: 20,
      ),
      Container(
        padding: const EdgeInsets.only(
          bottom: 10,
        ),
        decoration: kUpdateContainerDecoration,
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            Container(
              margin: const EdgeInsets.only(left: 15, top: 10),
              child: const Text(
                'Pending firmware information',
                style: kUpdateDetailsTitleStyle,
              ),
            ),
            const SizedBox(
              height: 5,
            ),
            Container(
              margin: const EdgeInsets.only(left: 15, top: 5),
              child: Text(
                '• Version: $g_NewSoftwareVersion',
                style: kUpdateDetailsStyle,
              ),
            ),
            const SizedBox(
              height: 5,
            ),
            Container(
              margin: const EdgeInsets.only(left: 15, top: 5),
              child: const Text(
                'What\'s new? ',
                style: kUpdateDetailsStyle,
              ),
            ),
            Container(
              margin:
                  const EdgeInsets.only(left: 15, top: 5, right: 11, bottom: 5),
              child: Text(
                g_SoftwareDescription.replaceAll(r'\n', '\n'),
                style: kUpdateDetailsStyle.copyWith(
                  fontSize: 14,
                  color: Colors.white,
                ),
              ),
            ),
          ],
        ),
      ),
      const SizedBox(
        height: 30,
      ),
      g_InstallStart
          ? Column(
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Text(
                      (installationPercentage < 100)
                          ? 'Installing....'
                          : 'Completed',
                      style: const TextStyle(
                        fontWeight: FontWeight.w600,
                        fontSize: 20,
                        color: Colors.white70,
                      ),
                    ),
                    const SizedBox(
                      width: 15,
                    ),
                    Text(
                      (installationPercentage < 100)
                          ? '$g_ESPInstallPercentage%'
                          : '',
                      style: const TextStyle(
                        fontWeight: FontWeight.bold,
                        fontSize: 16,
                        color: Colors.white70,
                      ),
                    ),
                  ],
                ),
                const SizedBox(
                  height: 20,
                ),
                Center(
                  child: LoadingAnimationWidget.inkDrop(
                    color: Colors.indigo,
                    size: 60,
                  ),
                )
              ],
            )
          : Column(
              children: [
                const Text(
                  'Waiting for Approval',
                  textAlign: TextAlign.center,
                  style: TextStyle(
                    fontWeight: FontWeight.w600,
                    fontSize: 18,
                    color: Colors.white,
                  ),
                ),
                const SizedBox(
                  height: 10,
                ),
                Center(
                  child: LoadingAnimationWidget.waveDots(
                    color: Colors.indigo,
                    size: 60,
                  ),
                )
              ],
            ),
    ],
  );
}
