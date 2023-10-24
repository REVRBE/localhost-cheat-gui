# localhost-cheat-gui PoC

This project leverages Boost Asio to establish a server bound to localhost:8080, functioning as an interactive GUI for changing settings in an external application. By engaging with the web interface hosted at localhost:8080, users can modify configurations and promptly update variables with their desired values. It can be accessed by any browser, meaning you can also use it in overlay specific browsers (Discord, Steam etc...)

It dynamically loads HTML, CSS, and JavaScript files from a specified path. Currently, it's configured to use the current directory, but you can easily customize the folder by updating the 'globals::full_path' variable with your desired path. Changing the website code is super easy as they're split up in their individual files.

If you're going to employ this in a cheat, I recommend encrypting/decrypting the website-code files. Personally I wrote a compile-time random string generator and got it generating 32 character string as secret_key in AES encryption for the files and I tried password protecting the files in .zip, but it didn't seem like there is any good libraries in C++ for setting the achieve password; it worked fine for files or folders inside a .zip. 

Since both the client and server are on localhost, it's less likely that any of the traffic being intercepted. I also recommend implementing TLS/SSL and use the keys already in .ssl from the %user% folder.


https://github.com/REVRBE/localhost-cheat-gui/assets/129604052/257d1cd4-d1fb-40a4-96c8-027ad8d1c94c



I have no plans of updating this; I just wanted to release it after quickly scrapping the pieces from my own personal source.
