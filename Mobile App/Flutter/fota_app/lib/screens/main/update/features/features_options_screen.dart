import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:fota_app/screens/main/update/features/features_screen.dart';
import 'package:loading_animation_widget/loading_animation_widget.dart';

import '../../../../components/alerts.dart';
import '../../../../constants/features_constant.dart';
import '../../../../constants/mqtt_topics.dart';

/* Disable buttons */
/* Firebase variables */
bool g_OTAUploadLED = false;
bool g_OTAUploadMotor = false;
/* Firebase topics */
final DatabaseReference databaseReferenceOTAUpload =
    FirebaseDatabase.instance.ref(kOTAUpload);
/* Download Percentage */
int downloadPercentage = int.tryParse(g_MQTTFeatureDownloadPercentage) ?? 0;

/* call back function  */
class FeaturesOptions extends StatefulWidget {
  const FeaturesOptions({
    super.key,
    required this.CallbackButtonPressedFunction,
  });
  final Function CallbackButtonPressedFunction;
  @override
  State<FeaturesOptions> createState() => _FeaturesOptionsState();
}

class _FeaturesOptionsState extends State<FeaturesOptions> {
  void ListenFun() {
    /* Car Features */ /* in case lw enta 3ayz tst5dm firebase instead of MQTTT */ /*
    databaseReferenceFeaturesButton.onValue.listen((DatabaseEvent event) {
      final CarFeatures = event.snapshot.value;
      if (event.snapshot.exists &&
          CarFeatures != null &&
          CarFeatures is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {});
      } else {
        print('Data type: ${CarFeatures.runtimeType}');
      }
    });*/
    /* Car Features */
    databaseReferenceCarFeatures.onValue.listen((DatabaseEvent event) {
      final CarFeatures = event.snapshot.value;
      if (event.snapshot.exists &&
          CarFeatures != null &&
          CarFeatures is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          g_LedFeature = CarFeatures['LED'] as bool;
          g_MotorFeature = CarFeatures['Motor'] as bool;
        });
      } else {
        print('Data type: ${CarFeatures.runtimeType}');
      }
    });
/* OTA */
    databaseReferenceOTAUpload.onValue.listen((DatabaseEvent event) {
      final OTAData = event.snapshot.value;
      if (event.snapshot.exists &&
          OTAData != null &&
          OTAData is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          /* if (OTAData['LED'] == 'true') {
            g_OTAUploadLED = true;
          } else {
            g_OTAUploadLED = false;
          }

          if (OTAData['Motor'] == 'true') {
            g_OTAUploadMotor = true;
          } else {
            g_OTAUploadMotor = false;
          }*/
          g_OTAUploadLED = OTAData['LED'] as bool;
          g_OTAUploadMotor = OTAData['Motor'] as bool;
        });
      } else {
        print('Data type: ${OTAData.runtimeType}');
      }
    });
  }

  void connectToMQTT() {
    /* bnbd2 n3ml listen  */
    MQTT_Feature_Service.listenForUpdates((String topic, String payload) {
      setState(() {
        bool payloadBOOL =
            payload.toLowerCase() == 'true'; // Convert payload to boolean
        /* hena de lw boolean function lazm tt3ml kda  */
        if (topic == kMQTTFeatureESPConfirmationFile) {
          /* hykon 3obarna 3nd send bs  */
          if (payload == kFeature_Message_Reject) {
            g_ConfirmDownloadLED = false;
            g_ConfirmDownloadMotor = false;
          } else if (payload == kFeature_Message_LED) {
            g_ConfirmDownloadLED = true;
            g_ConfirmDownloadMotor = false;
          } else if (payload == kFeature_Message_Motor) {
            g_ConfirmDownloadMotor = true;
            g_ConfirmDownloadLED = false;
          }
        } else if (topic == kMobileDisconnectTopic) {
        } else if (topic == kMQTTFeatureESPStartDownload) {
          g_MQTTFeatureESPStartDownload = payloadBOOL;
        } else if (topic == kMQTTFeatureESPDownloadPercentage) {
          g_MQTTFeatureDownloadPercentage = payload;
          downloadPercentage =
              int.tryParse(g_MQTTFeatureDownloadPercentage) ?? 0;
        } else if (topic == kMQTTFeatureESPDownloadComplete) {
          g_MQTTFeatureESPDownloadComplete = payloadBOOL;
        }
        /*------------------------------*/
      });
    });
  }

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    ListenFun();
    connectToMQTT();
  }

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
            'Pending Approval',
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
          if (g_LedFeatureRequests || g_MotorFeatureRequests)
            Column(
              crossAxisAlignment: CrossAxisAlignment.stretch,
              children: [
                g_LedFeatureRequests
                    ? Column(
                        /* Led feature container */
                        children: [
                          Container(
                            padding: const EdgeInsets.symmetric(
                                vertical: 20), // Adjust padding as needed
                            decoration: BoxDecoration(
                              border: Border(
                                bottom: BorderSide(
                                  color: Colors.white.withOpacity(
                                      0.5), // Adjust color and opacity as needed
                                  width: 0.8, // Adjust thickness as needed
                                ),
                              ),
                            ),
                            child: Column(
                              children: [
                                Row(
                                  children: [
                                    Expanded(
                                      child: Column(
                                        crossAxisAlignment:
                                            CrossAxisAlignment.stretch,
                                        children: [
                                          g_OTAUploadLED
                                              ? const Text(
                                                  'Request Accepted!',
                                                  style: TextStyle(
                                                      color: Color(0xee1a8f03),
                                                      fontSize: 18),
                                                  textAlign: TextAlign.start,
                                                )
                                              : Container(),
                                          const SizedBox(
                                            height: 5,
                                          ),
                                          Text(
                                            g_OTAUploadLED
                                                ? 'LED Feature Awaiting Your Confirmation for Download Initiation'
                                                : 'LED Feature Awaiting Approval',
                                            style: const TextStyle(
                                              color: Colors.white,
                                              fontSize:
                                                  15, // Adjust font size as needed
                                            ),
                                            textAlign: TextAlign.start,
                                          ),
                                        ],
                                      ),
                                    ),
                                    !g_OTAUploadLED
                                        ? SizedBox(
                                            height: 30,
                                            width: 70,
                                            child: RejectButton('LED'),
                                          )
                                        : Container(),
                                  ],
                                ),
                                const SizedBox(
                                  height: 15,
                                ),
                                g_OTAUploadLED
                                    ? Container(
                                        child: (g_MQTTFeatureESPStartDownload &&
                                                g_ConfirmDownloadLED)
                                            ? Column(
                                                children: [
                                                  Row(
                                                    mainAxisAlignment:
                                                        MainAxisAlignment
                                                            .center,
                                                    children: [
                                                      Text(
                                                        (downloadPercentage <
                                                                100)
                                                            ? 'Downloading..'
                                                            : 'Completed',
                                                        style: const TextStyle(
                                                          fontSize: 18,
                                                          fontWeight:
                                                              FontWeight.bold,
                                                          color: Colors.white70,
                                                        ),
                                                      ),
                                                      const SizedBox(
                                                        width: 15,
                                                      ),
                                                      Text(
                                                        (downloadPercentage <
                                                                100)
                                                            ? '$g_MQTTFeatureDownloadPercentage%'
                                                            : '',
                                                        style: const TextStyle(
                                                          fontWeight:
                                                              FontWeight.bold,
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
                                                          child: LoadingAnimationWidget
                                                              .fourRotatingDots(
                                                            color:
                                                                Colors.indigo,
                                                            size: 30,
                                                          ),
                                                        )
                                                      : Container(),
                                                ],
                                              )
                                            : g_ConfirmDownloadMotor
                                                ? const Text(
                                                    'Pending Download\nAnother Feature in Progress',
                                                    style: TextStyle(
                                                      fontSize: 14,
                                                      color: Colors.white70,
                                                    ),
                                                    textAlign: TextAlign.center,
                                                  )
                                                : AcceptanceButton(
                                                    g_ConfirmDownloadLED
                                                        ? 'Reject'
                                                        : 'Accept',
                                                    () {
                                                      setState(() {
                                                        widget
                                                            .CallbackButtonPressedFunction(
                                                                'LED');
                                                      });
                                                    },
                                                  ),
                                      )
                                    : Container()
                              ],
                            ),
                          ),
                        ],
                      )
                    : Container(),
                g_MotorFeatureRequests
                    ? Container(
                        padding: const EdgeInsets.symmetric(
                            vertical: 20), // Adjust padding as needed
                        decoration: BoxDecoration(
                          border: Border(
                            bottom: BorderSide(
                              color: Colors.white.withOpacity(
                                  0.5), // Adjust color and opacity as needed
                              width: 0.8, // Adjust thickness as needed
                            ),
                          ),
                        ),
                        child: Column(
                          children: [
                            Row(
                              children: [
                                Expanded(
                                  child: Column(
                                    crossAxisAlignment:
                                        CrossAxisAlignment.stretch,
                                    children: [
                                      g_OTAUploadMotor
                                          ? const Text(
                                              'Request Accepted!',
                                              style: TextStyle(
                                                  color: Color(0xee1a8f03),
                                                  fontSize: 18),
                                              textAlign: TextAlign.start,
                                            )
                                          : Container(),
                                      const SizedBox(
                                        height: 5,
                                      ),
                                      Text(
                                        g_OTAUploadMotor
                                            ? 'Motor Feature Awaiting Your Confirmation for Download Initiation'
                                            : 'Motor Feature Awaiting Approval',
                                        style: const TextStyle(
                                          color: Colors.white,
                                          fontSize:
                                              15, // Adjust font size as needed
                                        ),
                                        textAlign: TextAlign.start,
                                      ),
                                    ],
                                  ),
                                ),
                                !g_OTAUploadMotor
                                    ? SizedBox(
                                        height: 30,
                                        width: 70,
                                        child: RejectButton('Motor'),
                                      )
                                    : Container(),
                              ],
                            ),
                            const SizedBox(
                              height: 15,
                            ),
                            g_OTAUploadMotor
                                ? Container(
                                    child: g_ConfirmDownloadLED
                                        ? const Text(
                                            'Pending Download\nAnother Feature in Progress',
                                            style: TextStyle(
                                              fontSize: 14,
                                              color: Colors.white70,
                                            ),
                                            textAlign: TextAlign.center,
                                          )
                                        : AcceptanceButton(
                                            g_ConfirmDownloadMotor
                                                ? 'Reject'
                                                : 'Accept',
                                            () {
                                              setState(() {
                                                widget
                                                    .CallbackButtonPressedFunction(
                                                        'Motor');
                                              });
                                            },
                                          ),
                                  )
                                : Container()
                          ],
                        ),
                      )
                    : Container(),
              ],
            )
          else
            Container(
              margin: const EdgeInsets.only(top: 100),
              child: const Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Text(
                    'No pending features',
                    style: TextStyle(fontSize: 20, color: Colors.white54),
                  ),
                ],
              ),
            ),
          /* Your other widget when g_Requests is false */
        ],
      ),
    );
  }

  ElevatedButton RejectButton(String title) {
    return ElevatedButton(
      style: ButtonStyle(
        shape: const WidgetStatePropertyAll(RoundedRectangleBorder(
          borderRadius: BorderRadius.only(
            topRight: Radius.circular(15),
            topLeft: Radius.circular(10),
            bottomRight: Radius.circular(10),
            bottomLeft: Radius.circular(15),
          ),
        )),
        backgroundColor: WidgetStateProperty.all(const Color(0xbbab020f)),
      ),
      onPressed: () {
        setState(() {
          databaseReferenceRequests.update({title: false});
          Fluttertoast.cancel();
          toastFun('$title Feature Cancelled');
          Navigator.pop(context);
        });
      },
      child: const Icon(
        Icons.cancel,
        color: Colors.white,
      ),
    );
  }

  ElevatedButton AcceptanceButton(String title, Function() onPressed) {
    return ElevatedButton(
      style: ButtonStyle(
        shape: const WidgetStatePropertyAll(RoundedRectangleBorder(
          borderRadius: BorderRadius.only(
            topRight: Radius.circular(15),
            topLeft: Radius.circular(15),
            bottomRight: Radius.circular(15),
            bottomLeft: Radius.circular(15),
          ),
        )),
        backgroundColor: WidgetStateProperty.all(const Color(0xee11ABE1)),
      ),
      onPressed: onPressed,
      child: Text(
        title,
        style: const TextStyle(
          color: Colors.white,
          fontSize: 15,
        ),
      ),
    );
  }
}
