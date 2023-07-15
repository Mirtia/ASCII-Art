# ASCII art

## Notes

To use freetype you have to download the following libraries. I used *vcpkg*.

```bash
# VCPKG_DEFAULT_TRIPLET
vckpg install harfbuzz 
vckpg install freetype
```

Then, when configuring the build files you have to enable ```WITH_FREETYPE``` option. I also had to modify the ```CMakeLists.txt```  in OpenCV contributions [```/modules/freetype/CMakeLists.txt```](https://gist.github.com/UnaNancyOwen/14c72a3f10a46d41c359ab6ea307a1d2) to make it work.

Moreover, there were a ton of missing .dll files and there was no *GIF* file support from standard OpenCV. So I just used **ffmpeg** as a command line tool to convert resulting *.mp4* to *.gif*.

## Output examples

I do not own these images.

<img src="output/707.gif" alt="707" width="400">

<img src="output/smile-pepe.gif" alt="pepe" width="400">

<img src="output/osaka.jpg" alt="osaka" width="400">
