import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:fota_app/components/rounded_button.dart';
import 'package:fota_app/screens/main/list_tile/Support/support_loading_screen.dart';

import '../../../../components/alerts.dart';
import '../../../../constants/text_field.dart';
import '../../../../constants/update_screen_constants.dart';

/* Firebase topics */
final DatabaseReference _FirebaseSupportInfo =
    FirebaseDatabase.instance.ref("CAR_LIST/Elantra/MobileApp/Support");
/* Handle variable */
bool g_HandleState = true;
/* Screen ready variable  */
bool g_SupportScreenReady = false;
/* Message will be saved here */
String g_subject = '';
String g_Message = '';

class SupportScreen extends StatefulWidget {
  static String id = 'Support_Screen';

  const SupportScreen({super.key});

  @override
  State<SupportScreen> createState() => _SupportScreenState();
}

class _SupportScreenState extends State<SupportScreen> {
  Future<void> _FirstScreen() async {
    // Simulate a delay before refreshing
    final ref = FirebaseDatabase.instance
        .ref('CAR_LIST/Elantra/MobileApp/Support/HandleState');
    final snapshot = await ref.child('').get();
    bool HandleState = false; // default value
    if (snapshot.exists) {
      HandleState = snapshot.value as bool;
      setState(() {
        g_HandleState = HandleState;
      });
    } else {
      print('No data available.');
    }
  }

  void ListenFun() {
    /* Current states */
    _FirebaseSupportInfo.onValue.listen((DatabaseEvent event) {
      final dataCurrent = event.snapshot.value;
      if (event.snapshot.exists &&
          dataCurrent != null &&
          dataCurrent is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          g_HandleState = dataCurrent['HandleState'] as bool;
        });
      } else {
        print('Data type: ${dataCurrent.runtimeType}');
      }
    });
  }

  @override
  void initState() {
    super.initState();
    setState(() {
      g_SupportScreenReady = false;
      /* Update the first screen */
      _FirstScreen();
      // Listen for changes in the database
      ListenFun();
      g_SupportScreenReady = true;
    });
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    g_SupportScreenReady = false;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.black,
      appBar: AppBar(
        backgroundColor: Colors.black,
        title: const Text(
          'Support',
          style: TextStyle(
            color: Colors.white,
          ),
        ),
      ),
      body: g_SupportScreenReady
          ? SafeArea(
              child: g_HandleState
                  ? SingleChildScrollView(
                      // Wrap with SingleChildScrollView
                      child: Container(
                        padding: const EdgeInsets.symmetric(
                            vertical: 10,
                            horizontal: 10), // Adjust padding as needed
                        child: Column(
                          children: [
                            const SizedBox(
                              height: 30,
                            ),
                            Row(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                Container(
                                  margin: const EdgeInsets.only(
                                    left: 15,
                                  ),
                                  child: const Text(
                                    'Subject',
                                    style: TextStyle(fontSize: 20),
                                  ),
                                ),
                              ],
                            ),
                            const SizedBox(
                              height: 10,
                            ),
                            TextField(
                              textAlign: TextAlign.start,
                              textAlignVertical: TextAlignVertical.top,
                              style: const TextStyle(
                                color: Colors.white,
                              ),
                              onChanged: (value) {
                                //Do something with the user input.
                                g_subject = value;
                              },
                              decoration: kTextFieldDecoration.copyWith(
                                hintText: 'Enter Subject. ex: Purchase Support',
                              ),
                              maxLines:
                                  null, // or any large number depending on your needs
                            ),
                            const SizedBox(
                              height: 30,
                            ),
                            Row(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                Container(
                                  margin: const EdgeInsets.only(
                                    left: 15,
                                  ),
                                  child: const Text(
                                    'Message',
                                    style: TextStyle(fontSize: 20),
                                  ),
                                ),
                              ],
                            ),
                            const SizedBox(
                              height: 10,
                            ),
                            TextField(
                              textAlign: TextAlign.start,
                              textAlignVertical: TextAlignVertical.top,
                              style: const TextStyle(
                                color: Colors.white,
                              ),
                              onChanged: (value) {
                                //Do something with the user input.
                                g_Message = value;
                              },
                              decoration: kTextFieldDecoration.copyWith(
                                hintText: 'What do you need?',
                              ),
                              maxLines:
                                  null, // or any large number depending on your needs
                            ),
                            const SizedBox(
                              height: 30,
                            ),
                            SizedBox(
                                width: 120,
                                child: RoundedButton(
                                    title: 'Send',
                                    color: Colors.blueAccent,
                                    onPressed: () {
                                      setState(() {
                                        /* Check if it was empty or not   */
                                        if (g_subject == '' ||
                                            g_Message == '') {
                                          /* Send error message */
                                          errorCheck(
                                              context, 'SubjectMessageClear');
                                        } else {
                                          /* Send you subject */
                                          _FirebaseSupportInfo.update(
                                              {"Subject": g_subject});
                                          /* Send you message  */
                                          _FirebaseSupportInfo.update(
                                              {"Message": g_Message});
                                          /*Clear what is inside */
                                          g_subject = '';
                                          g_Message = '';
                                          /* Not handled */
                                          g_HandleState = false;
                                          _FirebaseSupportInfo.update(
                                              {"HandleState": g_HandleState});
                                          toastFun('Message Sent!');
                                        }
                                      });
                                    },
                                    labelSize: 20))
                            // Add more widgets here as needed
                          ],
                        ),
                      ),
                    )
                  : Container(
                      child: Column(
                        children: [
                          const SizedBox(
                            height: 30,
                          ),
                          Container(
                            decoration: kUpdateContainerDecoration.copyWith(
                                borderRadius: kContainerOnly),
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.stretch,
                              children: [
                                Container(
                                  margin:
                                      const EdgeInsets.only(left: 15, top: 10),
                                  child: const Text(
                                    'Pending Request',
                                    style: kUpdateTitleStyle,
                                  ),
                                ),
                                Container(
                                  margin:
                                      const EdgeInsets.only(left: 15, top: 5),
                                  child: const Text(
                                    'You have one pending message remaining. We will address it promptly. Should you prefer to cancel, please select the \'Cancel\' button.',
                                    style: kUpdateDetailsStyle,
                                  ),
                                ),
                                const SizedBox(
                                  height: 20,
                                ),
                              ],
                            ),
                          ),
                          const SizedBox(
                            height: 20,
                          ),
                          SizedBox(
                            width: 200,
                            child: RoundedButton(
                                title: 'Cancel Request',
                                color: const Color(0xffab020f),
                                onPressed: () {
                                  setState(() {
                                    g_HandleState = true;
                                    _FirebaseSupportInfo.update(
                                        {"HandleState": g_HandleState});
                                    /* Send you subject */
                                    _FirebaseSupportInfo.update(
                                        {"Subject": 'Cancelled'});
                                    /* Send you message  */
                                    _FirebaseSupportInfo.update(
                                        {"Message": 'Cancelled'});
                                    toastFun('Your case has been canceled!');
                                  });
                                },
                                labelSize: 20),
                          ),
                        ],
                      ),
                    ),
            )
          : SupportLoadingScreen(context),
    );
  }
}
