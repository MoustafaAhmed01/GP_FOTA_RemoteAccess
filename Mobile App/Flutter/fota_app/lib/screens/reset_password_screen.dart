import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';

import '../constants/update_screen_constants.dart';

bool g_LockApp = true;
late String g_LockAppPassword; // Replace with your desired password

final DatabaseReference _MobileLockApp =
    FirebaseDatabase.instance.ref("CAR_LIST/Elantra/MobileApp/LockApp");

class ResetPasswordScreen extends StatefulWidget {
  static String id = 'ResetPasswordScreen';
  final bool isMaster; // Define a variable to hold the passed boolean value
  const ResetPasswordScreen({super.key, required this.isMaster});

  @override
  _ResetPasswordScreenState createState() => _ResetPasswordScreenState();
}

class _ResetPasswordScreenState extends State<ResetPasswordScreen> {
  String oldPassword = "";
  String newPassword_1 = "";
  String newPassword_2 = "";

  void resetPassword() {
    if (oldPassword == g_LockAppPassword) {
      if (newPassword_1 == newPassword_2) {
        if (widget.isMaster == true) {
          setState(() {
            g_LockAppPassword = newPassword_1;
            _MobileLockApp.update(
              {
                "Password": g_LockAppPassword,
              },
            );
          });
          ScaffoldMessenger.of(context).showSnackBar(
            const SnackBar(
              content: Text(
                'Password was successfully changed',
                style: TextStyle(
                  color: Colors.white,
                ),
              ),
              backgroundColor: Colors.white12,
            ),
          );
          Navigator.of(context).pop();
        } else {
          ScaffoldMessenger.of(context).showSnackBar(
            const SnackBar(
              content: Text(
                'Only the owner who can change the password',
                style: TextStyle(
                  color: Colors.white,
                ),
              ),
              backgroundColor: Colors.white12,
            ),
          );
        }
        // Replace "1234" with the actual old password logic
      } else {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text(
              'New Password doesn\'t match',
              style: TextStyle(
                color: Colors.white,
              ),
            ),
            backgroundColor: Colors.white12,
          ),
        );
      }
    } else {
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(
          content: Text(
            'Old password is incorrect',
            style: TextStyle(
              color: Colors.white,
            ),
          ),
          backgroundColor: Colors.white12,
        ),
      );
    }
  }

/* Listen */
  void ListenFun() {
    /* Current states */
    _MobileLockApp.onValue.listen((DatabaseEvent event) {
      final dataCurrent = event.snapshot.value;
      if (event.snapshot.exists &&
          dataCurrent != null &&
          dataCurrent is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          g_LockApp = dataCurrent['State'] as bool;
          g_LockAppPassword = dataCurrent['Password'] as String;
        });
      } else {
        print('Data type: ${dataCurrent.runtimeType}');
      }
    });
  }

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    ListenFun();
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Reset Password'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: SingleChildScrollView(
          child: Container(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Container(
                  margin: const EdgeInsets.only(left: 15),
                  child: const Text(
                    'Remote Control Access',
                    style: TextStyle(
                      fontWeight: FontWeight.w600,
                      fontSize: 20,
                      color: Colors.white,
                    ),
                  ),
                ),
                const SizedBox(
                  height: 10,
                ),
                Container(
                  padding: const EdgeInsets.only(bottom: 20),
                  decoration: kUpdateContainerDecoration,
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.stretch,
                    children: [
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 10),
                        child: const Text(
                          'Vehicle\'s Information',
                          style: kUpdateDetailsTitleStyle,
                        ),
                      ),
                      const SizedBox(
                        height: 5,
                      ),
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 5),
                        child: Text(
                          '• Vehicle\'s current state : $g_LockApp',
                          style: kUpdateDetailsStyle,
                        ),
                      ),
                      const SizedBox(
                        height: 10,
                      ),
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 5),
                        child: const Text(
                          'Details ',
                          style: TextStyle(
                            fontWeight: FontWeight.w500,
                            fontSize: 14,
                            color: Color(0xffBfBfBB),
                          ),
                        ),
                      ),
                      Container(
                        margin: const EdgeInsets.only(left: 15, top: 5),
                        child: Text(
                          g_LockApp
                              ? '- The Current state is true which means your vehicle is locked and no one can access it using email and password. \n- If you wish to make it false and let anyone access your vehicle using username and password please re-enter your password again.'
                              : '- The Current state is false which means that your vehicle is unlocked and anyone can access it.\n- If you wish to lock your vehicle and only the car\'s owner has the access to it please re-enter the password again',
                          style: kUpdateDetailsStyle,
                        ),
                      ),
                    ],
                  ),
                ),
                const SizedBox(
                  height: 40,
                ),
                Container(
                  padding: const EdgeInsets.all(8),
                  decoration: BoxDecoration(
                    color: const Color(0xFF17171A),
                    borderRadius: BorderRadius.circular(25),
                  ),
                  child: Column(
                    children: [
                      TextField(
                        keyboardType: TextInputType.number,
                        obscureText: true,
                        decoration:
                            const InputDecoration(labelText: 'Old Password'),
                        onChanged: (value) {
                          setState(() {
                            oldPassword = value;
                          });
                        },
                      ),
                      TextField(
                        keyboardType: TextInputType.number,
                        obscureText: true,
                        decoration:
                            const InputDecoration(labelText: 'New Password'),
                        onChanged: (value) {
                          setState(() {
                            newPassword_1 = value;
                          });
                        },
                      ),
                      TextField(
                        keyboardType: TextInputType.number,
                        obscureText: true,
                        decoration: const InputDecoration(
                            labelText: 'Re-enter the password'),
                        onChanged: (value) {
                          setState(() {
                            newPassword_2 = value;
                          });
                        },
                      ),
                      const SizedBox(height: 20),
                      ElevatedButton(
                        onPressed: resetPassword,
                        child: const Text('Reset Password'),
                      ),
                    ],
                  ),
                ),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
