import 'package:flutter/material.dart';

import '../../../../constants/text_style&text_field.dart';

class speed_row extends StatelessWidget {
  const speed_row({super.key, required this.string, required this.speed});
  final String speed;
  final String string;

  @override
  Widget build(BuildContext context) {
    return Align(
      //alignment: Alignment.bottomRight,
      child: Container(
        margin: const EdgeInsets.only(bottom: 15),
        //padding: EdgeInsets.all(5),
        //alignment: Alignment.bottomRight,
        width: 150,
        decoration: BoxDecoration(
          border: const Border(
            left: BorderSide(
              color: Colors.blue, // Border color
              width: 2, // Border width
            ),
            right: BorderSide(
              color: Colors.blue, // Border color
              width: 2, // Border width
            ),
            top: BorderSide(
              color: Colors.blue, // Border color
              width: 2, // Border width
            ),
            bottom: BorderSide(
              color: Colors.blue, // Border color
              width: 2, // Border width
            ),
          ),
          color: Colors.black54,
          borderRadius: BorderRadius.circular(20),
        ),

        child: Row(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Text(string, style: kTextstyle_white),
            //SizedBox(height: 5),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              crossAxisAlignment: CrossAxisAlignment.baseline,
              textBaseline: TextBaseline.alphabetic,
              children: [
                /* if (speed =='unlimited')

                    Text(speed, style: kTextstyle_white)

                else
                 ...[*/

                Text(speed, style: kTextstyle_white),
                const Text('Km/h', style: kTextstyle_white)
                //]
              ],
            )
          ],
        ),
      ),
    );
  }
}
