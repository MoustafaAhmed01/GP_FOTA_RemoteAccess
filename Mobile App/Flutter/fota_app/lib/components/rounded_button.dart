import 'package:flutter/material.dart';

class RoundedButton extends StatefulWidget {
  const RoundedButton({
    super.key,
    required this.title,
    required this.color,
    required this.onPressed,
    required this.labelSize,
  });

  final Color color;
  final String title;
  final Function() onPressed;
  final double labelSize;

  @override
  _RoundedButtonState createState() => _RoundedButtonState();
}

class _RoundedButtonState extends State<RoundedButton> {
  bool _isPressed = false;

  @override
  Widget build(BuildContext context) {
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 16.0),
      child: Material(
        borderRadius: BorderRadius.circular(30.0),
        elevation: _isPressed ? 2.0 : 5.0,
        child: InkWell(
          onTap: widget.onPressed,
          borderRadius: BorderRadius.circular(30.0),
          onTapDown: (_) {
            setState(() {
              _isPressed = true;
            });
          },
          onTapCancel: () {
            setState(() {
              _isPressed = false;
            });
          },
          onTapUp: (_) {
            setState(() {
              _isPressed = false;
            });
          },
          child: Container(
            decoration: BoxDecoration(
              color: _isPressed ? widget.color.withOpacity(0.8) : widget.color,
              borderRadius: BorderRadius.circular(30.0),
            ),
            width: 200.0,
            height: 42.0,
            child: Center(
              child: Text(
                widget.title,
                style: TextStyle(
                  color: Colors.white,
                  fontSize: widget.labelSize,
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }
}
