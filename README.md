# Audio Production Tool (Qt, C++)

 Audio Production Tool is a cross-platform desktop application built with Qt and C++. It provides a suite of features for audio editing, mixing, and exporting.

## Features (In Progrss)

- All-in-one audio player, mixer, and synthesizer
- Multi-track audio editing
- Real-time effects and processing
- Import/export support for popular audio formats (WAV, MP3, FLAC)
- Non-destructive editing workflow
- Customizable interface

## Getting Started

### Prerequisites

- Qt 6.9
- CMake 3.25+
- C++17 compatible compiler
- Git/GitHub

### Build Instructions

```bash
git clone https://github.com/yourusername/audio-prod.git
cd audio-prod
git submodule --init --recursive
mkdir build && cd build
cmake ..
cmake --build .
```

## Usage

1. Launch the application.
2. Import audio files via the File menu.
3. Edit, mix, and apply effects as needed.
4. Export your project to your desired format.

## Contributing

Contributions are welcome! Please open issues or submit pull requests for improvements.

## Audio Metadata Library Attribution

This application uses TagLib, an open-source library for reading and editing metadata in popular audio formats (MP3, FLAC, Ogg Vorbis, AAC, WAV, AIFF, and more).

TagLib is distributed under the GNU Lesser General Public License (LGPL) and the Mozilla Public License (MPL)

- [Ogg Vorbis](https://xiph.org/vorbis/)
- [FLAC](https://xiph.org/flac/)
- [GNU Lesser General Public License](https://www.gnu.org/licenses/lgpl.html)
- [Mozilla Public License](https://www.mozilla.org/MPL/MPL-1.1.html)
