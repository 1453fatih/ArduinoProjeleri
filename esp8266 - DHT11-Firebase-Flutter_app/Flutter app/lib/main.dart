import 'package:firebase_auth/firebase_auth.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:google_sign_in/google_sign_in.dart';
import 'Dashboard.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter ile sıcaklık takibi',
      theme: ThemeData(
        primarySwatch: Colors.pink, //renk
      ),
      home: giris(title: 'Flutter ile sıcaklık takibi'),
      debugShowCheckedModeBanner: false,
    );
  }
}

class giris extends StatefulWidget {
  final String title;
  giris({Key key, this.title}) : super(key: key);

  @override
  _girisState createState() => _girisState();
}

class _girisState extends State<giris> {
  final FirebaseAuth firebaseAuth = FirebaseAuth.instance;
  GoogleSignIn _googleSignIn = GoogleSignIn(
    scopes: <String>['email'],
  );

  GoogleSignInAccount _currentUser;

  @override
  void initState() {
    super.initState();
    _googleSignIn.onCurrentUserChanged.listen((GoogleSignInAccount account) {
      setState(() {
        _currentUser = account;
      });

      if (_currentUser != null) {
        _handleFirebase();
      }
    });

    _googleSignIn.signInSilently();
  }

  void _handleFirebase() async {
    GoogleSignInAuthentication googleAuth = await _currentUser.authentication;
    final AuthCredential credential = GoogleAuthProvider.getCredential(
        idToken: googleAuth.idToken, accessToken: googleAuth.accessToken);

    final FirebaseUser firebaseUser =
        (await firebaseAuth.signInWithCredential(credential)).user;

    if (firebaseUser != null) {
      print('Giriş Başarılı aferimm ');

      Navigator.of(context).pushReplacement(
          new MaterialPageRoute(builder: (context) => new Dashboard()));
    }
  }

  Future<void> _handleSignIn() async {
    try {
      await _googleSignIn.signIn();
    } catch (error) {
      print(error);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(
        child: new Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              RaisedButton.icon(
                onPressed: () {
                  _handleSignIn();
                },
                color: Colors.blue,
                textColor: Colors.white,
                label: Text("Google Giris Yap"),
                icon: Icon(Icons.sentiment_very_satisfied),
              ),
              RaisedButton(
                child: Text("Daha Karpuz Kesecektik :("),
                color: Colors.blue,
                textColor: Colors.white,
                onPressed: () {
                  SystemChannels.platform.invokeMethod('SystemNavigator.pop');
                },
              )
            ]),
      ),
    );
  }
}
