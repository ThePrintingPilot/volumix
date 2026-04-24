<div align="center">

<img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-logo-256.png" width="140" alt="Volumix logo">

# Volumix

**Control the volume of every app on your PC with a real hardware mixer.**

</div>
<div align="center">
  <p>
    <a href="https://theprintingpilot.com"><img src="https://img.shields.io/badge/Website-ThePrintingPilot-00e5a0?logo=googlechrome&logoColor=white" alt="Website" /></a> 
    <a href="https://www.youtube.com/@ThePrintingPilot"><img src="https://img.shields.io/badge/YouTube-ThePrintingPilot-FF0000?logo=youtube&logoColor=white" alt="YouTube" /></a> 
<a href="https://github.com/ThePrintingPilot/volumix/releases/latest"><img src="https://img.shields.io/github/v/release/ThePrintingPilot/volumix?color=22c55e&label=download&logo=github&logoColor=white" alt="Download" /></a>
  </p>
  <p>
    <img src="https://img.shields.io/endpoint?url=https://bambu-light-mod.tomernassi.workers.dev/badge" alt="Active Devices" />
  </p>
</div>

---

## What is this?

Volumix turns a small DIY **Arduino Nano box with 5 sliders and 5 mute buttons** — a **Faderbox** — into a proper per-app volume mixer for Windows.

Discord getting too loud during a match? Slide it down without Alt-Tabbing. Want to mute Spotify the second a meeting starts? Smack the mute button. Each slider controls a specific app (or group of apps) of your choice.

No drivers. No cloud. No accounts. Just plug in the USB cable and you've got physical control of every sound coming out of your computer.


<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix.png" width="720" alt="Volumix main UI">
</div>

---

## What it can do

<img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/TPP-Mono.png" width="85" align="right" />

- **5 physical sliders** — each bound to any app (or group of apps) you choose
- **5 mute buttons** — instantly silence a channel without reaching for the mouse
- **Master volume** control on any slider
- **Multi-app per slider** — put Chrome + Firefox + Edge on one slider and it'll control all of them together
- **Real app icons** — Volumix reads the actual icon from each running app's .exe
- **Dark & light mode**
- **Auto-connect** — Faderbox auto-reconnects on startup
- **Start with Windows** — launches silently in the tray when you log in
- **Works offline** — no internet connection ever needed after install


<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/multi-app.png" width="100" alt="App picker window">
</div>

---

## What's a Faderbox?

A **Faderbox** is the hardware side of Volumix — a small box with 5 potentiometer sliders and 5 push buttons, wired up to an **Arduino Nano**. The Nano talks to your PC over USB, and Volumix listens.


<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/Midi_Controller_A-Camera_16.png" width="560" alt="Faderbox hardware">
</div>

---

## Deej Users

**Volumix** is built around the Arduino Nano and is fully compatible with existing **Deej** hardware builds. If you’re looking to migrate to a free solution with a modern, user-friendly GUI, Volumix makes it easy.

Simply upload our .ino file to your Arduino, and you’re ready to go — no hardware changes required.

## Hardware Wiring

```
Arduino Nano
├── A0 ── Potentiometer 1 
├── A1 ── Potentiometer 2 
├── A2 ── Potentiometer 3 
├── A3 ── Potentiometer 4 
├── A4 ── Potentiometer 5 
├── D2 ── Button 1
├── D3 ── Button 2
├── D4 ── Button 3
├── D5 ── Button 4
└── D6 ── Button 5
```


---

## Install

**Just want to use it? Grab the installer:**

### 👉 [Download the latest version](https://github.com/ThePrintingPilot/volumix/releases/latest)

1. Download `Volumix Setup x.x.x.exe` from the latest release
2. Run the installer
3. Launch Volumix from your Start menu or desktop shortcut
4. Plug in the Faderbox, open Volumix settings, click **Connect**
5. Assign apps to each slider — done

Volumix **updates itself automatically** through GitHub. When a new version is released, a notification slides in from the corner. One click to install.

---

## Using Volumix
<img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/TPP-Mono.png" width="85" align="right" />

### Assigning apps to a slider

1. Click any app pill below a slider (or the **+** on an empty one)
2. The app picker shows everything currently playing audio and everything with an open session
3. Check the apps you want that slider to control — you can pick multiple
4. Click **Done**

### Controlling multiple apps with one slider

Put Chrome, Firefox, and Edge all on the same slider → one physical control for "all browsers." Same trick works for games, chat apps, media players, whatever.

### Flipping a pot direction

If a slider moves the wrong way (up = quieter instead of louder), go to **Settings → Channels** and flip the switch for that channel. No need to re-solder anything.

### Mute buttons

Press any mute button on the Faderbox to instantly mute that channel. Press again to unmute and restore the previous volume.

### System tray

Close the window and Volumix keeps running in the system tray. Right-click the tray icon for quick access, or click it to show the window again.

---

## Settings

<!-- TODO: screenshot of settings window -->
<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-setting.png" width="560" alt="Settings window">
</div>


| Setting | What it does |
|---------|--------------|
| **Auto-connect** | Reconnects to your Faderbox automatically on startup |
| **Start on system boot** | Launches Volumix when Windows starts (hidden in tray) |
| **Start minimized** | App starts in the tray instead of showing the window |
| **Dark mode** | Dark-themed UI |
| **Pot direction** | Flip individual sliders if they're wired backwards |
| **Check for updates** | Manually check GitHub for newer versions |
| **Reset all settings** | Wipe everything and start over fresh |

---

## FAQ

**Do I need to install any drivers?**
No. Arduino Nanos with the standard CH340 chip are recognized by Windows 10/11 out of the box.

**Does Volumix work on Mac or Linux?**
Not yet. Volumix uses Windows-specific audio APIs (WASAPI). Cross-platform support isn't on the roadmap right now.

**Can I use fewer than 5 sliders?**
Yes. Unassigned sliders just do nothing. You can physically build a 2-slider or 3-slider Faderbox and the app will still work — the extra channels will just sit empty.

**Why does it take a second or two the first time I launch it?**
On first run, Volumix compiles a tiny helper program using your system's built-in C# compiler (no install needed — it ships with Windows). After that, it launches instantly.

**Can I use this with DaVinci Resolve / OBS / any specific app?**
If it shows up in the Windows Volume Mixer, it'll work with Volumix.



---

## Support the project
<img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/TPP-Mono.png" width="85" align="right" />

If Volumix made your setup better, the best way to help is to:

- ⭐ **Star this repo** so other people find it
- 🐛 **Report bugs** in [Issues](https://github.com/ThePrintingPilot/volumix/issues)
- 💡 **Suggest features** — I'm open to ideas

---
