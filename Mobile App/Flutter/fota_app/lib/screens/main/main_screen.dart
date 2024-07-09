import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:fota_app/constants/main_screen_constants.dart';
import 'package:fota_app/screens/main/emergency/emergency_screen.dart';
import 'package:fota_app/screens/main/location/location_screen.dart';
import 'package:fota_app/screens/main/remote_access/remote_access_options_screen.dart';
import 'package:fota_app/screens/main/update/firmware_features_screen.dart';

import '../../components/drawer_list.dart';
import '../../components/reusable_cards.dart';

class MainScreen extends StatefulWidget {
  static String id = 'Screen_Main';

  const MainScreen({super.key});

  @override
  State<MainScreen> createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  final _auth = FirebaseAuth.instance;
  late User? loggedInUser = _auth.currentUser;
  final GlobalKey<ScaffoldState> _scaffoldKey = GlobalKey<ScaffoldState>();

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        key: _scaffoldKey,
        drawer: drawerList(),
        body: Container(
          decoration: const BoxDecoration(
            image: DecorationImage(
              image: AssetImage('images/img.png'),
              fit: BoxFit.cover,
            ),
          ),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Container(
                padding: const EdgeInsets.all(10),
                decoration: const BoxDecoration(
                  color: Colors.black26,
                ),
                child: Row(
                  children: [
                    Flexible(
                      child: Hero(
                        tag: 'logo',
                        child: SizedBox(
                          height: 20,
                          child: Image.asset('images/FOTA_Logo.png'),
                        ),
                      ),
                    ),
                    const SizedBox(
                      width: 20,
                    ),
                    const Text(
                      'FOTA Team',
                      style: TextStyle(
                        fontSize: 20,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                  ],
                ),
              ),
              Container(
                margin: const EdgeInsets.only(left: 10, top: 20),
                decoration: const BoxDecoration(
                  shape: BoxShape.circle,
                  color: Colors.black87,
                ),
                child: IconButton(
                  onPressed: () {
                    _scaffoldKey.currentState!.openDrawer();
                  },
                  icon: const Icon(
                    Icons.menu,
                    size: 30,
                  ),
                ),
              ),
              const SizedBox(
                height: 60,
              ),
              longCard(
                  kLongWidgetColor,
                  const Padding(
                    padding: EdgeInsets.all(10.0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.center,
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Text(
                          'Car Remote Access',
                          style: TextStyle(
                            fontWeight: FontWeight.bold,
                            fontSize: 30,
                            color: Colors.white70,
                          ),
                        ),
                      ],
                    ),
                  ), () {
                /* Navigate to remote access screen */
                showModalBottomSheet(
                  context: context,
                  builder: (context) => const RemoteAccessOptions(),
                );
              }, 'images/remote_access.png'),
              longCard(
                kLongWidgetColor,
                Padding(
                  padding: const EdgeInsets.all(10.0),
                  child: Container(
                    child: const Center(
                      child: Text(
                        'Current Location',
                        style: TextStyle(
                          fontWeight: FontWeight.bold,
                          fontSize: 30,
                          color: Colors.white70,
                        ),
                      ),
                    ),
                  ),
                ),
                () {
                  Navigator.pushNamed(context, LocationScreen.id);
                },
                'images/location.png',
              ),
              Row(
                children: [
                  Expanded(
                    child: thinCard(
                      kLongWidgetColor,
                      const Column(
                        mainAxisAlignment: MainAxisAlignment.center,
                        children: [
                          Center(
                            child: Text(
                              'Firmware &\nFeatures',
                              textAlign: TextAlign.center,
                              style: TextStyle(
                                fontWeight: FontWeight.bold,
                                fontSize: 30,
                                color: Colors.white70,
                              ),
                            ),
                          ),
                          Icon(
                            Icons.update,
                            size: 40,
                            color: Colors.white70,
                          ),
                        ],
                      ),
                      () {
                        Navigator.pushNamed(
                            context, Firmware_Features_Screen.id);
                      },
                      'images/update.png',
                    ),
                  ),
                  Expanded(
                    child: thinCard(
                        kLongWidgetColor,
                        const Column(
                          crossAxisAlignment: CrossAxisAlignment.center,
                          children: [
                            SizedBox(
                              height: 20,
                            ),
                            Text(
                              'Emergency',
                              textAlign: TextAlign.center,
                              style: TextStyle(
                                fontWeight: FontWeight.bold,
                                fontSize: 30,
                                color: Colors.white70,
                              ),
                            ),
                            Icon(
                              Icons.emergency_share_rounded,
                              size: 40,
                              color: Colors.white70,
                            ),
                          ],
                        ), () {
                      Navigator.pushNamed(context, EmergencyScreen.id);
                    }, 'images/emergency.png'),
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }
}
