import 'package:flutter/material.dart';

class TeamInfo extends StatelessWidget {
  static String id = 'TeamInfo_Screen';

  const TeamInfo({super.key});

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        appBar: AppBar(
          backgroundColor: Colors.black,
          title: const Text(
            'Team Members',
            style: TextStyle(fontWeight: FontWeight.bold),
          ),
          centerTitle: true,
        ),
        body: Container(
          color: Colors.black54,
          child: Column(
            children: [
              Container(
                margin: const EdgeInsets.only(
                  top: 100,
                  right: 10,
                ),
                child: const Row(
                  children: [
                    Expanded(
                      child: Column(
                        children: [
                          CircleAvatar(
                            radius: 50,
                            backgroundImage:
                                AssetImage('images/Team/ahmed.png'),
                          ),
                          SizedBox(
                            height: 10,
                          ),
                          Text('Ahmed Hatem'),
                        ],
                      ),
                    ),
                    Expanded(
                      child: Column(
                        children: [
                          CircleAvatar(
                            radius: 50,
                            backgroundImage:
                                AssetImage('images/Team/moustafa.png'),
                          ),
                          SizedBox(
                            height: 10,
                          ),
                          Text('Moustafa Ahmed'),
                        ],
                      ),
                    ),
                    Expanded(
                      child: Column(
                        children: [
                          CircleAvatar(
                            radius: 50,
                            backgroundImage:
                                AssetImage('images/Team/shady.png'),
                          ),
                          SizedBox(
                            height: 10,
                          ),
                          Text('Shady Alaa'),
                        ],
                      ),
                    ),
                  ],
                ),
              ),
              Container(
                margin: const EdgeInsets.only(
                  top: 100,
                  right: 10,
                ),
                child: const Row(
                  children: [
                    Expanded(
                      child: Column(
                        children: [
                          CircleAvatar(
                            radius: 50,
                            backgroundImage: AssetImage('images/Team/seif.png'),
                          ),
                          SizedBox(
                            height: 10,
                          ),
                          Text('Seif Ayman'),
                        ],
                      ),
                    ),
                    Expanded(
                      child: Column(
                        children: [
                          CircleAvatar(
                            radius: 50,
                            backgroundImage:
                                AssetImage('images/Team/esraa.png'),
                          ),
                          SizedBox(
                            height: 10,
                          ),
                          Text('Esraa Ali'),
                        ],
                      ),
                    ),
                  ],
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
