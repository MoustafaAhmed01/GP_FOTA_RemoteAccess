import 'package:animated_text_kit/animated_text_kit.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:fota_app/screens/main/list_tile/about_us.dart';
import 'package:fota_app/screens/main/list_tile/settings.dart';
import 'package:fota_app/screens/main/list_tile/team_info.dart';

import '../constants/loading_screen_constants.dart';
import '../screens/main/list_tile/Support/support.dart';
import 'alerts.dart';

class drawerList extends StatelessWidget {
  final _auth = FirebaseAuth.instance;
  late User? loggedInUser = _auth.currentUser;

  drawerList({super.key});

  @override
  Widget build(BuildContext context) {
    return Drawer(
      shape: const RoundedRectangleBorder(
        borderRadius: BorderRadius.only(
            topRight: Radius.circular(80), bottomRight: Radius.circular(30)),
      ),
      backgroundColor: Colors.black87,
      // Drawer content goes here
      child: ListView(
        padding: const EdgeInsets.all(0),
        children: <Widget>[
          DrawerHeader(
            decoration: const BoxDecoration(
              color: Colors.indigo,
            ),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                AnimatedTextKit(
                  animatedTexts: [
                    ColorizeAnimatedText(
                      'FOTA \nCar Remote Access Team',
                      textStyle: const TextStyle(
                        fontSize: 20,
                        fontWeight: FontWeight.bold,
                      ),
                      speed: const Duration(milliseconds: 800),
                      colors: colorizeColors,
                    ),
                  ],
                  isRepeatingAnimation: true,
                ),
              ],
            ),
          ),

          ListTile(
            title: const Text(
              'Team Info',
              style: TextStyle(
                fontSize: 20,
              ),
            ),
            onTap: () {
              // Handle item 1 tap
              Navigator.pushNamed(context, TeamInfo.id);
            },
          ),
          ListTile(
            title: const Text(
              'About',
              style: TextStyle(
                fontSize: 20,
              ),
            ),
            onTap: () {
              // Handle item 2 tap
              Navigator.pushNamed(context, AboutTeam.id);
            },
          ),
          ListTile(
            title: const Row(
              children: [
                Text(
                  'Support',
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                SizedBox(
                  width: 10,
                ),
                Icon(
                  Icons.support_agent,
                  color: Colors.white70,
                  size: 20,
                )
              ],
            ),
            onTap: () {
              // Handle item 2 tap
              Navigator.pushNamed(context, SupportScreen.id);
            },
          ),
          ListTile(
            title: const Row(
              children: [
                Text(
                  'Settings',
                  style: TextStyle(
                    fontSize: 20,
                  ),
                ),
                SizedBox(
                  width: 10,
                ),
                Icon(
                  Icons.settings,
                  color: Colors.white,
                  size: 20,
                )
              ],
            ),
            onTap: () {
              // Handle item 2 tap
              Navigator.pushNamed(context, AppSettings.id);
            },
          ),
          ListTile(
            title: const Row(
              children: [
                Text(
                  'Log out',
                  style: TextStyle(
                    fontSize: 20,
                    color: Colors.red,
                  ),
                ),
                SizedBox(
                  width: 10,
                ),
                Icon(
                  Icons.logout,
                  color: Colors.white,
                  size: 20,
                ),
              ],
            ),
            onTap: () {
              // Handle item 2 tap
              _auth.signOut();
              toastFun('Signed Out!');
              Navigator.of(context).popUntil((route) => route.isFirst);
            },
          ),
          // Add more ListTile widgets for additional items
        ],
      ),
    );
  }
}
