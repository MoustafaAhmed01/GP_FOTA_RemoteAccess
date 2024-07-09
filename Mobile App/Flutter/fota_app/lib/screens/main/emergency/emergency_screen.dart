import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:fota_app/components/alerts.dart';
import 'package:fota_app/constants//colours.dart';
import 'package:fota_app/screens/main/emergency/emergency_loading_screen.dart';

import '../../../Service/mqtt_service.dart';
import '../../../constants/mqtt_topics.dart';
import '../../../constants/text_style&text_field.dart';
import '../location/location_screen.dart';
import '../remote_access/speed/speed_control_screen.dart';

/* Global Variables */
String g_enable_disable = 'DISABLED';
String g_Car_Feedback = 'DISABLED';
bool g_EmergencyScreenReady = false;
List<String> g_Emergency_state = [
  'ENABLED',
  'DISABLED',
];

class EmergencyScreen extends StatefulWidget {
  static String id = "Screen_Emergency";

  const EmergencyScreen({super.key});

  @override
  State<EmergencyScreen> createState() => _EmergencyScreenState();
}

class _EmergencyScreenState extends State<EmergencyScreen> {
  String en_dis_string = g_enable_disable;
  Color stop_colour_in = kActivewhite12;
  Color location_colour_in = kActivewhite12;
  TextStyle text_style = kTextstyle3_white12;

  late MQTTService mqttService;
  /* MQTT FUNCTION */
  void connectToMQTT() {
    mqttService = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    mqttService.connect([
      kMobileDisconnectTopic,
      kenable_disableemergencyTopic,
      kLimitedSpeedTopic,
      kEmergencyFeedback,
      kMQTTinit,
    ]);

    mqttService.listenForUpdates((String topic, String payload) {
      setState(() {
        bool updateState =
            payload.toLowerCase() == 'true'; // Convert payload to boolean
        if (topic == kenable_disableemergencyTopic) {
        } else if (topic == kEmergencyFeedback) {
          g_Car_Feedback = payload;
          g_enable_disable = payload;
          if (g_Car_Feedback == g_Emergency_state[1]) {
            en_dis_string = g_Emergency_state[1];
            stop_colour_in = kActivewhite12;
            location_colour_in = kActivewhite12;
            text_style = kTextstyle3_white12;
          } else if (g_Car_Feedback == g_Emergency_state[0]) {
            en_dis_string = g_Emergency_state[0];
            stop_colour_in = kActivewhite12;
            location_colour_in = kActivewhite12;
            text_style = kTextstyle3_white;
          }
        } else if (topic == kLimitedSpeedTopic) {
          unlimitedspeed = payload;
        } else if (topic == kMQTTinit) {
          mqttService.publishMessage(
              kMobileDisconnectTopic, 'Emergency Screen CONNECTED', kNotRetain);
          g_EmergencyScreenReady = true;
        }
      });
    });
  }

  @override
  void initState() {
    super.initState();
    g_EmergencyScreenReady = false;
    /* Initialize MQTT */
    connectToMQTT();
    /* Update the first screen */
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    g_EmergencyScreenReady = false;
    mqttService.publishMessage(kMQTTinit, 'true', kRetain);
    mqttService.publishMessage(
        kMobileDisconnectTopic, 'Emergency Screen DISCONNECTED', kNotRetain);
    mqttService.disconnect();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        appBar: AppBar(
          backgroundColor: Colors.black,
          title: const Text(
            'Emergency',
            style: TextStyle(color: Colors.white),
          ),
        ),
        body: g_EmergencyScreenReady
            ? Container(
                decoration: const BoxDecoration(
                  image: DecorationImage(
                    image: AssetImage(
                        'images/leather_1.png'), // Path to your image
                    fit: BoxFit.cover,
                    alignment: Alignment.centerRight,
                  ),
                ),
                child: Column(
                  children: [
                    Image.asset(
                      'images/car.png',
                    ),
                    Row(
                      mainAxisAlignment: MainAxisAlignment.center,
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        Container(
                          width: 85,
                          height: 85,
                          decoration: const BoxDecoration(
                            shape: BoxShape.circle,
                            border: Border(
                              left: BorderSide(
                                color: Colors.white30, // Border color
                                width: 10, // Border width
                              ),
                            ),
                            color: Colors.black54,
                          ),
                          child: GestureDetector(
                              child: const Icon(
                                Icons.lock_open_outlined,
                                size: 40,
                                color: Colors.white30,
                              ),
                              onTap: () {
                                if (g_Car_Feedback == g_Emergency_state[1]) {
                                  //enable
                                  setState(() {
                                    Fluttertoast.cancel();
                                    toastFun('Enable Request sent!');
                                    //stop_colour_in = kActivewhite12;
                                    //location_colour_in = kActivewhite12;
                                    g_enable_disable = g_Emergency_state[0];
                                    //en_dis_string = g_enable_disable;
                                    //text_style = kTextstyle3_white;
                                    /*publish message through mqtt*/
                                    mqttService.publishMessage(
                                        kenable_disableemergencyTopic,
                                        g_enable_disable,
                                        kRetain);
                                  });
                                }
                              }),
                        ),
                        const SizedBox(
                          width: 10,
                        ),
                        Container(
                          width: 120,
                          height: 110,
                          decoration: const BoxDecoration(
                            shape: BoxShape.circle,
                            border: Border(
                              left: BorderSide(
                                color: Colors.white30, // Border color
                                width: 10, // Border width
                              ),
                            ),
                            color: Colors.black54,
                          ),
                          child: Center(
                            child: Text(
                              en_dis_string,
                              style: kTextstyle_white,
                            ),
                          ),
                        ),
                        const SizedBox(
                          width: 10,
                        ),
                        Container(
                          width: 85,
                          height: 85,
                          decoration: const BoxDecoration(
                            shape: BoxShape.circle,
                            border: Border(
                              left: BorderSide(
                                color: Colors.white30, // Border color
                                width: 10, // Border width
                              ),
                            ),
                            color: Colors.black54,
                          ),
                          child: GestureDetector(
                              child: const Icon(
                                Icons.lock_outlined,
                                size: 40,
                                color: Colors.white30,
                              ),
                              onTap: () {
                                if (g_Car_Feedback == g_Emergency_state[0]) {
                                  //enable
                                  setState(() {
                                    Fluttertoast.cancel();
                                    toastFun('Disable Request sent!');
                                    g_enable_disable = g_Emergency_state[1];
                                    // stop_colour_in = kActivewhite12;
                                    //location_colour_in = kActivewhite12;
                                    //en_dis_string = g_enable_disable;
                                    //text_style = kTextstyle3_white12;
                                    /*publish message through mqtt*/
                                    mqttService.publishMessage(
                                        kenable_disableemergencyTopic,
                                        g_enable_disable,
                                        kRetain);
                                  });
                                }
                              }),
                        ),
                      ],
                    ),
                    const SizedBox(
                      height: 20,
                    ),
                    Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        Container(
                          height: 80,
                          width: 200,
                          decoration: BoxDecoration(
                            color: stop_colour_in,
                            borderRadius: BorderRadius.circular(10),
                            shape: BoxShape.rectangle,
                          ),
                          child: Center(
                            child: GestureDetector(
                              child: Text(
                                'Stop Car',
                                style: text_style,
                              ),
                              onTap: () {
                                if (g_enable_disable == g_Emergency_state[0]) {
                                  setState(() {
                                    stop_colour_in = Colors.white24;
                                    location_colour_in = kActivewhite12;
                                    unlimitedspeed = '0';

                                    /*publish message through mqtt*/
                                    mqttService.publishMessage(
                                        kLimitedSpeedTopic,
                                        unlimitedspeed,
                                        kRetain);
                                  });
                                }
                              },
                            ),
                          ),
                        ),

                        const SizedBox(
                          height: 15,
                        ),
                        Container(
                          height: 80,
                          width: 200,
                          decoration: BoxDecoration(
                            color: location_colour_in,
                            borderRadius: BorderRadius.circular(10),
                            shape: BoxShape.rectangle,
                          ),
                          child: Center(
                            child: GestureDetector(
                              child: Text(
                                'Location',
                                style: text_style,
                              ),
                              onTap: () {
                                if (g_enable_disable == g_Emergency_state[0]) {
                                  setState(() {
                                    location_colour_in = Colors.white24;
                                    stop_colour_in = kActivewhite12;
                                    Navigator.pushNamed(
                                            context, LocationScreen.id)
                                        .then(
                                      (value) => connectToMQTT(),
                                    );
                                  });
                                }
                              },
                            ),
                          ),
                        ),
                        // ),
                      ],
                    )
                    //),
                    // ],
                    // )
                  ],
                ),
              )
            : EmergencyLoadingScreen(context),
      ),
    );
  }
}
