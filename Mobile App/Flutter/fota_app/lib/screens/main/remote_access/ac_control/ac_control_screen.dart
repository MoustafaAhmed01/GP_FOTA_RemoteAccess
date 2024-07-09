import 'package:flutter/material.dart';

import '../../../../Service/mqtt_service.dart';
import '../../../../constants/colours.dart';
import '../../../../constants/mqtt_topics.dart';
import '../../../../constants/text_style&text_field.dart';
import 'ac_title_container.dart';

String g_tempstate = '';
String g_fanstate = '';

List<String> g_fanspeedstate = [
  'Stop',
  'Low',
  'Medium',
  'High',
];
List<String> g_temperaturestate = [
  'Hot',
  'Normal',
  'Cold',
];

class AirCondControlScreen extends StatefulWidget {
  static String id = "Screen_AC";

  const AirCondControlScreen({super.key});
  @override
  State<AirCondControlScreen> createState() => _AirCondControlScreenState();
}

class _AirCondControlScreenState extends State<AirCondControlScreen> {
  late MQTTService mqttService;
  /* MQTT FUNCTION */
  void connectToMQTT() {
    mqttService = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    mqttService.connect([
      kMobileDisconnectTopic,
      kFanSpeedTopic,
      kTemperatureTopic,
    ]);

    mqttService.listenForUpdates((String topic, String payload) {
      setState(() {
        String updateState = payload;
        /* hena de lw boolean function lazm tt3ml kda  */
        if (topic == kTemperatureTopic) {
          g_tempstate = updateState;
          //g_previoustempstate=updateState;
        } else if (topic == kFanSpeedTopic) {
          g_fanstate = updateState;
          //g_previousfanstate=updateState;
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
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    //mqttService.disconnect();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        /*leading: IconButton(
        icon: Icon(Icons.speed_rounded),
          onPressed: () {  },
        ),*/
        title: const Text(
          'Air Conditioner',
          style: TextStyle(color: Colors.white),
        ),
      ),
      body: Container(
        decoration: const BoxDecoration(
          image: DecorationImage(
            image: AssetImage('images/AC1.jpeg'), // Path to your image
            fit: BoxFit.cover,
          ),
        ),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          crossAxisAlignment: CrossAxisAlignment.stretch,
          children: [
            //AC_column1(colour_container1:Colors.white30 ,colour_container2: Colors.grey,),
            //AC_column2(colour_container1:Colors.white30 ,colour_container2: Colors.grey,),
            Expanded(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: [
                  const title_container(text: 'Temperature'),
                  const SizedBox(
                    height: 20,
                  ),
                  Container(
                    margin: const EdgeInsets.all(10),
                    padding: const EdgeInsets.all(10),
                    height: 400,
                    decoration: BoxDecoration(
                      color: Colors.black87,
                      borderRadius: BorderRadius.circular(50),
                    ),
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        temp_container(g_temperaturestate[0], kActivecolourHot,
                            kInactivecolourHot),
                        const SizedBox(
                          height: 15,
                        ),
                        temp_container(g_temperaturestate[1],
                            kActivecolourNormal, kInactivecolourNormal),
                        const SizedBox(
                          height: 15,
                        ),
                        temp_container(g_temperaturestate[2], kActivecolourCold,
                            kInactivecolourCold),
                        const SizedBox(
                          height: 0,
                        ),
                      ],
                    ),
                  ),
                ],
              ),
            ),
            Expanded(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.stretch,
                children: [
                  const title_container(text: 'Fan Speed'),
                  const SizedBox(
                    height: 20,
                  ),
                  Container(
                    margin: const EdgeInsets.all(10),
                    padding: const EdgeInsets.all(10),
                    height: 400,
                    decoration: BoxDecoration(
                      color: Colors.black87,
                      borderRadius: BorderRadius.circular(50),
                    ),
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        fan_container(g_fanspeedstate[0]),
                        fan_container(g_fanspeedstate[1]),
                        fan_container(g_fanspeedstate[2]),
                        fan_container(g_fanspeedstate[3]),
                      ],
                    ),
                  ),
                ],
              ),
            )
          ],
        ),
      ),
    );
  }

  Container fan_container(String fanspeed) {
    return Container(
      width: 120,
      margin: const EdgeInsets.all(5),
      //padding: EdgeInsets.only(top: 5, bottom: 5),
      decoration: BoxDecoration(
        color: g_fanstate == fanspeed ? kActivecolour : kInactivecolour,
        borderRadius: BorderRadius.circular(50),
      ),
      child: GestureDetector(
        onTap: () {
          setState(() {
            g_fanstate = fanspeed;
            /*publish message through mqtt*/
            mqttService.publishMessage(kFanSpeedTopic, g_fanstate, kNotRetain);
          });
        },
        child: Center(
          child: Text(
            fanspeed,
            style: kTextstyle3_white,
          ),
        ),
      ),
    );
  }

  Container temp_container(String temp, Color active, Color inactive) {
    return Container(
      margin: const EdgeInsets.all(10),
      //padding: EdgeInsets.only(top: 8, bottom: 8),
      decoration: BoxDecoration(
        color: g_tempstate == temp ? active : inactive,
        borderRadius: BorderRadius.circular(50),
      ),
      child: Container(
        margin: const EdgeInsets.all(5),
        //padding: EdgeInsets.only(top: 3, bottom: 3),
        decoration: BoxDecoration(
          color: active,
          borderRadius: BorderRadius.circular(50),
        ),
        child: GestureDetector(
          onTap: () {
            setState(() {
              g_tempstate = temp;
              /*publish message through mqtt*/
              mqttService.publishMessage(
                  kTemperatureTopic, g_tempstate, kNotRetain);
            });
          },
          child: Text(
            temp,
            style: kTextstyle3_white,
          ),
        ),
      ),
    );
  }
}
