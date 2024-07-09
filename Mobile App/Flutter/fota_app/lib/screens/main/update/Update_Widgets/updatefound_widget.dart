import 'package:flutter/material.dart';
import 'package:loading_animation_widget/loading_animation_widget.dart';

import '../../../../constants/update_screen_constants.dart';
import 'update_screen.dart';

typedef ConfirmationCallBack = Function();

Widget UpdateFoundContainer(ConfirmationCallBack onPressed) {
  int downloadPercentage = int.tryParse(g_ESPDownloadPercentage) ?? 0;

  return Container(
    child: Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Container(
          margin: const EdgeInsets.only(left: 15),
          child: const Text(
            'New Firmware update found',
            style: kUpdateTitleStyle,
          ),
        ),
        const SizedBox(
          height: 15,
        ),
        Center(
          child: Container(
            height: 100,
            width: 1000, // Adjust the width to make it a perfect circle
            decoration: kUpdateContainerDecoration.copyWith(
              borderRadius: kImageWithContainerBorders,
            ),
            child: ClipRRect(
              borderRadius: kImageWithContainerBorders,
              child: const Image(
                image: AssetImage('images/NewUpdateFound.png'),
                fit:
                    BoxFit.cover, // Use BoxFit.cover to cover the entire circle
              ),
            ),
          ),
        ),
        const SizedBox(
          height: 5,
        ),
        Container(
          decoration: kUpdateContainerDecoration.copyWith(
              borderRadius: kImageContainer),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              Container(
                margin: const EdgeInsets.only(left: 15, top: 5),
                child: const Text(
                  'What\'s new? ',
                  style: kUpdateDetailsStyle,
                ),
              ),
              Container(
                margin: const EdgeInsets.only(left: 15, top: 5),
                child: Text(
                  g_SoftwareDescription.replaceAll(r'\n', '\n'),
                  style: kUpdateDetailsStyle.copyWith(
                    fontSize: 14,
                    color: Colors.white,
                  ),
                ),
              ),
              const SizedBox(
                height: 25,
              )
            ],
          ),
        ),
        const SizedBox(
          height: 40,
        ),
        Container(
          decoration:
              kUpdateContainerDecoration.copyWith(borderRadius: kContainerOnly),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              Container(
                margin: const EdgeInsets.only(left: 15, top: 10),
                child: const Text(
                  'Update Information',
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
              Container(
                margin: const EdgeInsets.only(left: 15, top: 5),
                child: Text(
                  '• Date: $g_SoftwareDate',
                  style: kUpdateDetailsStyle,
                ),
              ),
              Container(
                margin: const EdgeInsets.only(left: 15, top: 5),
                child: Text(
                  '• File name: $g_FileName',
                  style: kUpdateDetailsStyle,
                ),
              ),
              const SizedBox(
                height: 25,
              ),
            ],
          ),
        ),
        const SizedBox(
          height: 50,
        ),
        (g_ConfirmUpdate == true)
            ? (g_ESPStartedDownload == true)
                ? Column(
                    children: [
                      Row(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          Text(
                            (downloadPercentage < 100)
                                ? 'Downloading..'
                                : 'Completed',
                            style: const TextStyle(
                              fontSize: 20,
                              fontWeight: FontWeight.bold,
                              color: Colors.white70,
                            ),
                          ),
                          const SizedBox(
                            width: 15,
                          ),
                          Text(
                            (downloadPercentage < 100)
                                ? '$g_ESPDownloadPercentage%'
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
                        height: 10,
                      ),
                      (downloadPercentage < 100)
                          ? Center(
                              child: LoadingAnimationWidget.fourRotatingDots(
                                color: Colors.indigo,
                                size: 60,
                              ),
                            )
                          : Container(),
                    ],
                  )
                : ConfirmationButton(onPressed)
            : ConfirmationButton(onPressed),
      ],
    ),
  );
}

Center ConfirmationButton(ConfirmationCallBack onPressed) {
  return Center(
    child: ElevatedButton(
      onPressed: () {
        onPressed();
      },
      style: const ButtonStyle(
        backgroundColor: WidgetStatePropertyAll(Color(0xFF11ABE1)),
        elevation: WidgetStatePropertyAll(30),
        padding: WidgetStatePropertyAll(
          EdgeInsets.only(left: 40, right: 40),
        ),
      ),
      child: Text(
        g_ConfirmUpdate ? 'Reject' : 'Confirm',
        style: const TextStyle(
          color: Colors.white,
        ),
      ),
    ),
  );
}
