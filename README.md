# uc::apng::loader
**uc::apng::loader** is a header only C++11  APNG (Animated PNG) decoder.

## Example

### Load from APNG file

```cpp
auto loader = uc::apng::create_file_loader(filename);

std::cout << "\"" << filename << "\" " 
	<< "(" << loader.width() << "x" << loader.height() << "), " 
	<< loader.num_frames() << "frames, " 
	<< loader.num_plays() << " times to loop (0 indicates infinite looping).\n";
```

### Load APNG frames

```cpp
std::vector<uc::apng::frame> frames;
while (!loader.eof() && (frames.size() < loader.num_frames())) {
	frames.push_back(loader.next_frame());
}
```

### Write to PNG file (using `stb_image_write.h`)

```cpp
size_t i = 0;
for (auto&& frame : frames) {
	std::ostringstream os;
	os << "out" << std::setw(3) << std::setfill('0') << i << ".png";
	auto outputfile = os.str();

	stbi_write_png(outputfile.c_str(), frame.image.width(), frame.image.height(), 4, frame.image.data(), frame.image.width() * 4);
	++i;
}
```

### Rendering Animation

```cpp
for (uint32_t i = 0; (loader.num_plays() == 0) || (i < loader.num_plays()); ++i) {

	for (auto&& frame : frames) {

		//
		// render frame
		//

		std::this_thread::sleep_for(std::chrono::microseconds(1000000) * frame.delay_num / frame.delay_den);
	}
}
```




## Requirements

* C++11 support compiler
* [stb_image.h]<https://github.com/nothings/stb>

## Sample Code

### Build & Execute

```bash
$ g++ -std=c++11 apng2pngs.cpp
$ ./a.out Animated_PNG_example_bouncing_beach_ball.apng
```

## Test

### Build & Execute

```bash
$ g++ -std=c++11 test.cpp
$ ./a.out
```

## License

MIT License

## References

* [APNG Specification](https://wiki.mozilla.org/APNG_Specification#.60fcTL.60:_The_Frame_Control_Chunk)
