import 'package:flutter/material.dart';

import '../../../../Service/mqtt_service.dart';
import '../../../../components/alerts.dart';
import '../../../../constants/colours.dart';
import '../../../../constants/mqtt_topics.dart';
import '../../../../constants/text_style&text_field.dart';
import 'Gaugeview.dart';
import 'speed_container.dart';
import 'speed_row.dart';

String g_currentspeed = '0';
String g_limitedspeed = '480';
Color setcolour = kActivecolourCold;
Color unlimitcolour = kActivecolourCold;
String string = 'Enter Speed Limit ';
String limitedspeed = '';
bool g_animategauge = true;
String unlimitedspeed = '480';

class SpeedControlScreen extends StatefulWidget {
  static String id = "Screen_Speed";

  const SpeedControlScreen({super.key});

  @override
  State<SpeedControlScreen> createState() => _SpeedControlScreenState();
}

class _SpeedControlScreenState extends State<SpeedControlScreen> {
  late MQTTService mqttService;

  /* MQTT FUNCTION */
  void connectToMQTT() {
    mqttService = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    mqttService.connect([
      kMobileDisconnectTopic,
      kCurrentSpeedTopic,
      kLimitedSpeedTopic,
    ]);

    mqttService.listenForUpdates((String topic, String payload) {
      setState(() {
        String updateState = payload;

        if (topic == kCurrentSpeedTopic) {
          g_currentspeed = updateState;
        } else if (topic == kLimitedSpeedTopic) {
          if (updateState == '0') {
            unlimitedspeed = updateState;
          } else {
            g_limitedspeed = updateState;
            unlimitedspeed = g_limitedspeed;
          }
        }

        /*------------------------------*/
      });
    });
  }

  @override
  void initState() {
    super.initState();

    /* Initialize MQTT */
    connectToMQTT();
    /* Update the first screen */
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    mqttService.disconnect();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      resizeToAvoidBottomInset: true,
      appBar: AppBar(
        /*leading: IconButton(
          icon: Icon(Icons.arrow_back),
          onPressed: () {
            // Navigate back to Speed_Screen
            // mqttService.disconnect();
            //Navigator.pop(context);// Pop PreviousScreen from the stack
            Navigator.push(
              context,
              MaterialPageRoute(
                builder: (context) {
                  return EmergencyScreen();
                },
              ),
            );
          },
        ),*/
        title: const Text(
          'Speed Control',
          style: TextStyle(color: Colors.white),
        ),
      ),
      body: Stack(
        fit: StackFit.expand,
        children: [
          Image.asset(
            'images/leather_1.png',
            fit: BoxFit.cover,
          ),
          SingleChildScrollView(
            padding: const EdgeInsets.only(top: 100),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  crossAxisAlignment: CrossAxisAlignment.center,
                  children: [
                    /*Speed_container(
                      colour: Colors.black54,
                      child: speed_column(
                          string: 'Current Speed', speed: g_currentspeed,),
                    ),
                    /*Speed_container(
                        colour: Colors.black54,
                        child: speed_column(
                            string: 'Max Speed', speed: g_limitedspeed,)),*/
                  */
                    Gaugeview(
                      currentspeed: g_currentspeed,
                      maxspeed: g_limitedspeed,
                      boolen: g_animategauge,
                    )
                  ],
                ),
                speed_row(
                  string: 'Max: ',
                  speed: unlimitedspeed,
                ),
                //SizedBox(height: 40),
                Container(
                  margin: const EdgeInsets.only(left: 15, right: 15),
                  padding: const EdgeInsets.only(left: 20, right: 20),
                  decoration: BoxDecoration(
                    color: Colors.black54,
                    borderRadius: BorderRadius.circular(50),
                  ),
                  child: TextField(
                    keyboardType: TextInputType.number,
                    cursorColor: Colors.white,
                    keyboardAppearance: Brightness.dark,
                    textAlign: TextAlign.center,
                    onChanged: (value) {
                      setState(() {
                        limitedspeed = value;
                        /*publish message through mqtt*/
                        /* mqttService.publishMessage(
                            kLimitedSpeedTopic, g_limitedspeed, kRetain);
                      */
                      });
                    },
                    decoration:
                        kTextFieldDecoration.copyWith(labelText: string),
                    style: kTextstyle_white,
                  ),
                ),
                Row(
                  crossAxisAlignment: CrossAxisAlignment.center,
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Speed_container(
                      colour: setcolour,
                      child: buildGestureDetector('set'),
                    ),
                    Speed_container(
                      colour: unlimitcolour,
                      child: buildGestureDetector('unlimit'),
                    ),
                  ],
                )
              ],
            ),
          ),
        ],
      ),
    );
  }

  GestureDetector buildGestureDetector(String text) {
    return GestureDetector(
      child: Center(child: Text(text, style: kTextstyle_white)),
      onTap: () {
        setState(() {
          if (text == 'set') {
            if (limitedspeed == '' || int.parse(limitedspeed) > 480) {
              setcolour = kActivecolourCold;
              unlimitcolour = kdarkblue;
              //g_limitedspeed = '480'; // Set to default limit
              errorCheck(context, 'SpeedClear');
            } else {
              setcolour = kdarkblue;
              unlimitcolour = kActivecolourCold;
              string = 'Enter Speed Limit ';
              g_limitedspeed = limitedspeed;
            }
          } else {
            unlimitcolour = kdarkblue;
            setcolour = kActivecolourCold;
            string = 'Enter Speed Limit ';
            g_limitedspeed = '480'; // Set to default limit
          }
          /*publish message through mqtt*/
          mqttService.publishMessage(
              kLimitedSpeedTopic, g_limitedspeed, kNotRetain);
        });
      },
    );
  }
}
