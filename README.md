# Gambatte-K2: Game Boy Emulator for Kindle (GTK2/FBInk)

**Gambatte-K2** is a Game Boy / Game Boy Color (`.gb`, `.gbc` ROMS) emulator frontend for Kindle e-ink devices, built with performance in mind. It leverages the [gambatte-libretro](https://github.com/libretro/gambatte-libretro) core and provides a GTK2 interface, as well as direct framebuffer rendering mode via [FBInk](https://github.com/NiLuJe/FBInk).

---

## Usage

Grab the zip (`gambatte-k2.zip`), unpack on `/mnt/us/extensions` as any other extension:

Launch via KUAL and/or copy the shortcut (`shortcut_gambatte-k2.sh`) to `/mnt/us/documents` so it shows on your library.

## TL-DR Technical Features

- **Fast, Lightweight UI:**  
  Minimal dependencies (`2.5Mb` binary), runs pretty well on low-RAM e-ink Kindles using around `15Mb` of RAM.
- **Two Rendering Modes:**  
  - **GTK2:** Standard X11/GTK2 drawing mode using the OS e-ink refreshing.
  - **FBInk:** Direct framebuffer output for maximum speed, a little quirky, with more ghosting.
- **Performance-Oriented Design:**  
  - Only **one main loop** in the frame processing path doing scaling and dithering at once.
  - **Ordered dithering (BW)** (Bayer 4x4) applied during a first scaling stage for improved frame speed processing.
  - **Nearest-neighbor scaling** in the second stage for fast upscaling.
  - **Single GdkPixbuf** reused for all frames to minimize RAM usage and allocations.
  - **LUT (Lookup Table):** Precomputed 65536-entry lookup table with RGB565→RGB888→grayscale conversion for fast pixel processing.
- **Touch & Multi-Touch Controls:**  
  - On-screen virtual Game Boy like buttons with ad-hoc multi-touch support (up to 2 touches) listening directly on the `/dev/input/eventX` device events.
- **Dynamic Quality/Size Controls:**  
  - Toggle between some scaling/quality presets.
- **Threaded Frame Processing:**  
  - Frame conversion and drawing are offloaded to a worker thread to keep the UI responsive.
- **Minimal External Dependencies:**  
  - Only needs GTK2, GDK-Pixbuf, and FBInk (for direct mode).

---


