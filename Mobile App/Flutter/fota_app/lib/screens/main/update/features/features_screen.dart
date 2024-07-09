import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:fota_app/components/alerts.dart';
import 'package:fota_app/components/rounded_button.dart';
import 'package:fota_app/constants/features_constant.dart';
import 'package:loading_animation_widget/loading_animation_widget.dart';

import '../../../../Service/mqtt_service.dart';
import '../../../../constants/mqtt_topics.dart';
import '../../../../constants/update_screen_constants.dart';
import 'features_loading_screen.dart';
import 'features_options_screen.dart';

/* Pending Button */
bool g_FeaturePressed = false;
/* Acceptance button */
bool g_ConfirmDownloadLED = false;
bool g_ConfirmDownloadMotor = false;
/* Screen Variables */
bool g_FeaturesScreenReady = false;
bool g_NothingToBuy = false;
/* MQTT Variables */
bool g_MQTTFeatureESPStartDownload = false;
String g_MQTTFeatureDownloadPercentage = '0';
bool g_MQTTFeatureESPDownloadComplete = false;
bool g_FBMobileAppConfirmationButton = false;
/* Features Variables */
late bool g_LedFeature;
late bool g_MotorFeature;
/* Pending */
late bool g_LedFeatureRequests;
late bool g_MotorFeatureRequests;
/* List */
List<String> featureList = ['none'];
String _selectedFeature = 'none';
/* Pressed on buy or not */
bool g_BuyButtonPressed = false;
/*MQTT*/
late MQTTService MQTT_Feature_Service;
/* Firebase topic*/
final DatabaseReference databaseReferenceCarFeatures =
    FirebaseDatabase.instance.ref(kCarFeatures);
final DatabaseReference databaseReferenceRequests =
    FirebaseDatabase.instance.ref(kFeaturesRequests);

/*final DatabaseReference databaseReferenceFeaturesButton =
    FirebaseDatabase.instance.ref(kFeaturesButtonTopic);*/

class Features_Screen extends StatefulWidget {
  static String id = 'Features_Screen';

  const Features_Screen({super.key});

  @override
  State<Features_Screen> createState() => _Features_ScreenState();
}

class _Features_ScreenState extends State<Features_Screen> {
  /* Confirmation Button */
  void ConfirmationButtonPressed(String FeatureSelected) {
    if (FeatureSelected == 'LED') {
      /* Publish the requested message to the mqtt topic */
      g_ConfirmDownloadLED
          ? g_ConfirmDownloadLED = false
          : g_ConfirmDownloadLED = true;
      /*databaseReferenceFeaturesButton.update({'LED': g_ConfirmDownloadLED});*/
      MQTT_Feature_Service.publishMessage(
          kMQTTFeatureESPConfirmationFile,
          g_ConfirmDownloadLED ? kFeature_Message_LED : kFeature_Message_Reject,
          kRetain);
    } else if (FeatureSelected == 'Motor') {
      g_ConfirmDownloadMotor
          ? g_ConfirmDownloadMotor = false
          : g_ConfirmDownloadMotor = true;
      MQTT_Feature_Service.publishMessage(
          kMQTTFeatureESPConfirmationFile,
          g_ConfirmDownloadMotor
              ? kFeature_Message_Motor
              : kFeature_Message_Reject,
          kRetain);
      /* databaseReferenceFeaturesButton.update({'Motor': g_ConfirmDownloadMotor});*/
    } else {}
  }

  void resetBuyButtonPressed() {
    setState(() {
      g_BuyButtonPressed = true;
    });

    Future.delayed(const Duration(seconds: 1), () {
      setState(() {
        g_BuyButtonPressed = false;
        /* Toast that you bought this feature */
        Fluttertoast.cancel();
        toastFun('Successful Purchase');
        if (featureList.length <= 1) {
          g_NothingToBuy = true;
        } else {
          g_NothingToBuy = false;
        }
      });
    });
  }

  /* Download Complete Function */
  void FeatureDownloadComplete(String FeatureDownloaded) {
    setState(() {
/*      databaseReferenceFeaturesButton.update({'LED': false});
      databaseReferenceFeaturesButton.update({'Motor': false});*/
      g_ConfirmDownloadLED = false;
      g_ConfirmDownloadMotor = false;
      /* Return back the Confirmation to Cancel */
      MQTT_Feature_Service.publishMessage(
          kMQTTFeatureESPConfirmationFile, kFeature_Message_Reject, kRetain);
      /*  */
      g_MQTTFeatureESPDownloadComplete = false;
      MQTT_Feature_Service.publishMessage(
          kMQTTFeatureESPDownloadComplete, 'false', kRetain);
      /**/
      g_MQTTFeatureDownloadPercentage = '0';
      MQTT_Feature_Service.publishMessage(
          kMQTTFeatureESPDownloadPercentage, '0', kRetain);
      /**/
      g_MQTTFeatureESPStartDownload = false;
      MQTT_Feature_Service.publishMessage(
          kMQTTFeatureESPStartDownload, 'false', kRetain);
    });
  }

  /* Firebase Listen */
  void ListenFun() {
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
          if (g_LedFeature == true) {
            FeatureDownloadComplete('LED');
            g_LedFeatureRequests = false;
            databaseReferenceRequests.update({'LED': g_LedFeatureRequests});
          }
          if (g_MotorFeature == true) {
            FeatureDownloadComplete('Motor');
            g_MotorFeatureRequests = false;
            databaseReferenceRequests.update({'Motor': g_MotorFeatureRequests});
          }
        });
      } else {
        print('Data type: ${CarFeatures.runtimeType}');
      }
    });
    /* Requests */
    databaseReferenceRequests.onValue.listen((DatabaseEvent event) {
      final FireBaseRequests = event.snapshot.value;
      if (event.snapshot.exists &&
          FireBaseRequests != null &&
          FireBaseRequests is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          g_LedFeatureRequests = FireBaseRequests['LED'] as bool;
          g_MotorFeatureRequests = FireBaseRequests['Motor'] as bool;

          /* Refresh the list again */
          featureList = ['none']; // Clear the list before adding new items
          _selectedFeature = 'none';
          FireBaseRequests.forEach((key, value) {
            if (value is bool && value == false) {
              if (key == 'LED') {
                if (g_LedFeature == true) {
                  featureList.remove(key);
                } else {
                  featureList.add(key as String);
                  g_NothingToBuy = false;
                }
              }
              if (key == 'Motor') {
                if (g_MotorFeature == true) {
                  featureList.remove(key);
                } else {
                  featureList.add(key as String);
                  g_NothingToBuy = false;
                }
              }
            } else if (value is bool && value == true) {
              featureList.remove(key);
            }
          });
        });
      } else {
        print('Data type: ${FireBaseRequests.runtimeType}');
      }
    });
  }

  void connectToMQTT() {
    MQTT_Feature_Service = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    MQTT_Feature_Service.connect([
      kMQTTFeatureESPConfirmationFile,
      kMQTTFeatureESPStartDownload,
      kMQTTFeatureESPDownloadPercentage,
      kMQTTFeatureESPDownloadComplete,
      kMQTTinit,
    ]);
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
        } else if (topic == kMQTTFeatureESPDownloadComplete) {
          g_MQTTFeatureESPDownloadComplete = payloadBOOL;
          if (g_MQTTFeatureESPDownloadComplete == true) {
          } else {}
        } else if (topic == kMQTTinit) {
          MQTT_Feature_Service.publishMessage(
              kMobileDisconnectTopic, 'Features Screen CONNECTED', kNotRetain);
          /* Topic to initialize the MQTT in the update screen */
          g_FeaturesScreenReady = true;
        }
        /*------------------------------*/
      });
    });
  }

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    g_FeaturesScreenReady = false;

    connectToMQTT();
    ListenFun();

    if (featureList.length <= 1) {
      g_NothingToBuy = true;
    } else {
      g_NothingToBuy = false;
    }
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    g_FeaturesScreenReady = false;
    /* refresh the page ready flag */
    MQTT_Feature_Service.publishMessage(kMQTTinit, 'true', kRetain);
    MQTT_Feature_Service.publishMessage(
        kMobileDisconnectTopic, 'Features Screen DISCONNECTED', kNotRetain);
    MQTT_Feature_Service.disconnect();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.black,
      appBar: AppBar(
        backgroundColor: Colors.black,
        title: const Text(
          'Features',
          style: TextStyle(
            color: Colors.white,
          ),
        ),
      ),
      body: g_FeaturesScreenReady
          ? SafeArea(
              child: SizedBox.expand(
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  crossAxisAlignment: CrossAxisAlignment.end,
                  children: [
                    Container(
                      margin: const EdgeInsets.only(top: 10),
                      child: Column(
                        children: [
                          Container(
                            decoration: kUpdateContainerDecoration.copyWith(
                                borderRadius: kContainerOnly),
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.stretch,
                              children: [
                                const SizedBox(
                                  height: 10,
                                ),
                                Container(
                                  margin:
                                      const EdgeInsets.only(left: 15, top: 5),
                                  child: const Text(
                                    'Features',
                                    style: TextStyle(
                                      color: Colors.white,
                                      fontSize: 20,
                                    ),
                                  ),
                                ),
                                Container(
                                  margin:
                                      const EdgeInsets.only(left: 15, top: 5),
                                  child: const Text(
                                    'Your vehicle includes all basics features plus the below features. If required feature isn\'t available for you, just request it',
                                    style: kUpdateDetailsStyle,
                                  ),
                                ),
                                const SizedBox(
                                  height: 15,
                                ),
                              ],
                            ),
                          ),
                          const SizedBox(
                            height: 15,
                          ),
                          Container(
                            decoration: kUpdateContainerDecoration.copyWith(
                                borderRadius: kContainerOnly),
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.stretch,
                              children: [
                                const SizedBox(
                                  height: 10,
                                ),
                                Container(
                                  margin:
                                      const EdgeInsets.only(left: 15, top: 5),
                                  child: const Text(
                                    'Upgrade',
                                    style: TextStyle(
                                      color: Colors.white,
                                      fontSize: 20,
                                    ),
                                  ),
                                ),
                                (g_MotorFeature || g_LedFeature)
                                    ? Column(
                                        crossAxisAlignment:
                                            CrossAxisAlignment.start,
                                        children: [
                                          Container(
                                            margin: const EdgeInsets.only(
                                                left: 15, top: 5),
                                            child: const Text(
                                              'You have the following Features:',
                                              style: kUpdateDetailsStyle,
                                            ),
                                          ),
                                          g_MotorFeature
                                              ? Container(
                                                  margin: const EdgeInsets.only(
                                                      left: 30, top: 5),
                                                  child: const Text(
                                                    '⦿ Motor Feature',
                                                    style: kUpdateDetailsStyle,
                                                  ),
                                                )
                                              : Container(),
                                          g_LedFeature
                                              ? Container(
                                                  margin: const EdgeInsets.only(
                                                      left: 30, top: 5),
                                                  child: const Text(
                                                    '⦿ LED Feature',
                                                    style: kUpdateDetailsStyle,
                                                  ),
                                                )
                                              : Container(),
                                        ],
                                      )
                                    : Column(
                                        crossAxisAlignment:
                                            CrossAxisAlignment.start,
                                        children: [
                                          Container(
                                            margin: const EdgeInsets.only(
                                                left: 15, top: 5),
                                            child: const Text(
                                              'You are on Basic Mode',
                                              style: kUpdateDetailsStyle,
                                            ),
                                          ),
                                          const SizedBox(
                                            height: 10,
                                          ),
                                          Container(
                                            margin: const EdgeInsets.only(
                                                left: 15, top: 5),
                                            child: const Text(
                                              'If you aspire to enhance your vehicle\'s capabilities, kindly consider purchasing the requisite features listed below.',
                                              style: kUpdateDetailsStyle,
                                            ),
                                          )
                                        ],
                                      ),
                                const SizedBox(
                                  height: 15,
                                ),
                              ],
                            ),
                          ),
                          const SizedBox(
                            height: 20,
                          ),
                          (g_NothingToBuy == false)
                              ? Container(
                                  decoration: kUpdateContainerDecoration
                                      .copyWith(borderRadius: kContainerOnly),
                                  child: Column(
                                    crossAxisAlignment:
                                        CrossAxisAlignment.stretch,
                                    children: [
                                      const SizedBox(height: 10),
                                      Container(
                                        margin: const EdgeInsets.only(
                                            left: 15, top: 5),
                                        child: const Text(
                                          'Feature Acquisition',
                                          style: TextStyle(
                                            color: Colors.white,
                                            fontSize: 20,
                                          ),
                                        ),
                                      ),
                                      const SizedBox(height: 15),
                                      Container(
                                        margin: const EdgeInsets.only(left: 10),
                                        child: const Text(
                                          'Select the feature you wish to buy',
                                          style: TextStyle(fontSize: 15),
                                        ),
                                      ),
                                      const SizedBox(
                                        height: 0,
                                      ),
                                      Column(
                                        crossAxisAlignment:
                                            CrossAxisAlignment.end,
                                        children: [
                                          featureList.isNotEmpty
                                              ? DropdownButton<String>(
                                                  value: _selectedFeature
                                                          .isNotEmpty
                                                      ? _selectedFeature
                                                      : null,
                                                  onChanged:
                                                      (String? newValue) {
                                                    setState(() {
                                                      _selectedFeature =
                                                          newValue!;
                                                    });
                                                  },
                                                  items: featureList
                                                      .map((String value) {
                                                    return DropdownMenuItem<
                                                        String>(
                                                      value: value,
                                                      child: Text(value),
                                                    );
                                                  }).toList(),
                                                )
                                              : const Text(
                                                  'Max Upgrade',
                                                  style:
                                                      TextStyle(fontSize: 15),
                                                ),
                                        ],
                                      ),
                                      const SizedBox(height: 15),
                                      Container(
                                        height: 75,
                                        margin: const EdgeInsets.only(
                                            left: 120, right: 120),
                                        child: g_BuyButtonPressed
                                            ? Container(
                                                child: LoadingAnimationWidget
                                                    .fourRotatingDots(
                                                  color:
                                                      const Color(0xff1128bf),
                                                  size: 30,
                                                ),
                                              )
                                            : BuyButton(),
                                      ),
                                    ],
                                  ),
                                )
                              : Container(),
                        ],
                      ),
                    ),
                    Container(
                      margin: const EdgeInsets.only(bottom: 30, right: 5),
                      width: 180,
                      child: ElevatedButton(
                        style: ButtonStyle(
                          elevation: WidgetStateProperty.all(5),
                          backgroundColor:
                              WidgetStateProperty.all(Colors.black12),
                        ),
                        onPressed: () {
                          showModalBottomSheet(
                            context: context,
                            builder: (context) => SingleChildScrollView(
                              child: FeaturesOptions(
                                CallbackButtonPressedFunction:
                                    ConfirmationButtonPressed,
                              ),
                            ),
                          );
                        },
                        child: const Row(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            Text(
                              'Details List',
                              style: TextStyle(
                                color: Colors.white70,
                              ),
                            ),
                            SizedBox(width: 20),
                            Icon(
                              Icons.checklist_rtl_sharp,
                              color: Colors.white70,
                            ),
                          ],
                        ),
                      ),
                    ),
                  ],
                ),
              ),
            )
          : FeaturesLoadingScreen(context),
    );
  }

  RoundedButton BuyButton() {
    return RoundedButton(
      title: 'Buy',
      color: Colors.blueAccent,
      onPressed: () {
        setState(
          () {
            if (_selectedFeature == 'LED') {
              /* Loading Button */
              resetBuyButtonPressed();
              /* Publish the requested message to the mqtt topic */

              /* Set data on firebase to true as it's requested */
              databaseReferenceRequests.update({"LED": true});
              featureList.remove(_selectedFeature);
            } else if (_selectedFeature == 'Motor') {
              /* Loading Button */
              resetBuyButtonPressed();

              /* Set data on firebase to true as it's requested */
              databaseReferenceRequests.update({"Motor": true});
              featureList.remove(_selectedFeature);
            } else {
              /* Toast that you bought this feature */
              Fluttertoast.cancel();
              toastFun('Select an item');
            }
            _selectedFeature = 'none';
          },
        );
      },
      labelSize: 18,
    );
  }
}
