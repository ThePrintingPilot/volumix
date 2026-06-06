<div align="center">

<img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-logo-256.png" width="140" alt="Volumix logo">

# Volumix

**Control the volume of every app on your PC with a real hardware mixer.**

</div>
<div align="center">
  <p>
    <a href="https://theprintingpilot.com"><img src="https://img.shields.io/badge/Website-ThePrintingPilot-00e5a0?logo=googlechrome&logoColor=white" alt="Website" /></a> 
    <a href="https://www.youtube.com/@ThePrintingPilot"><img src="https://img.shields.io/badge/YouTube-ThePrintingPilot-FF0000?logo=youtube&logoColor=white" alt="YouTube" /></a> 
        <a href="https://discord.gg/eNYyHBM7cM"><img src="https://img.shields.io/badge/Discord-Volumix-5865F2?logo=discord&logoColor=white" alt="Discord" /></a> 
<a href="https://github.com/ThePrintingPilot/volumix/releases/latest"><img src="https://img.shields.io/github/v/release/ThePrintingPilot/volumix?color=22c55e&label=download&logo=github&logoColor=white" alt="Download" /></a>
  </p>
  <p>
    <img src="https://img.shields.io/endpoint?url=https://bambu-light-mod.tomernassi.workers.dev/volumix/badge" alt="Active Users" />
  </p>
</div>

---

## What is this?

Volumix turns a small DIY **Arduino Nano box with 5 sliders and 5 mute buttons** — a **Faderbox** — into a proper per-app volume mixer for Windows.

Discord getting too loud during a match? Slide it down without Alt-Tabbing. Want to mute Spotify the second a meeting starts? Smack the mute button. Each slider controls a specific app (or group of apps) of your choice.

No drivers. No cloud. No accounts. Just plug in the USB cable and you've got physical control of every sound coming out of your computer.


<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-main.gif" width="720" alt="Volumix main UI">
</div>

---

## What it can do

<img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/TPP-Mono.png" width="85" align="right" />

### Hardware control
- **5 physical sliders** — each bound to any app (or group of apps) you choose
- **5 mute buttons** — instantly silence a channel without reaching for the mouse
- **Master volume** control on any slider
- **Mic & input device control** — assign your microphone to a slider; mute button hard-mutes it system-wide

### Smart audio handling
- **Multi-app per slider** — put Chrome + Firefox + Edge on one slider and it'll control all of them together
- **Custom slider names** — right-click any pill to rename it (e.g. "Browsers" or "Voice")
- **Smart device switching** — switch from speakers to headphones and audio instantly snaps to whatever the Faderbox shows. No more sudden volume jumps when Windows remembers the last per-device setting
- **Real app icons** — Volumix reads the actual icon from each running app's .exe

### Quality of life
- **Dark & light mode**
- **Auto-connect** — Faderbox auto-reconnects on startup
- **Start with Windows** — launches silently in the tray when you log in
- **Works offline** — no internet connection ever needed after install


<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/multi-app.png" width="100" alt="App picker window">
</div>

---

## DIY builders & Deej users

**Volumix** is built around the Arduino Nano and is fully compatible with existing **Deej** hardware builds. Want to build your own Faderbox, or migrate from Deej to a modern, free GUI? Both work the same way.

Grab the open firmware from the [`open-firmware/`](https://github.com/ThePrintingPilot/volumix/tree/main/open-firmware) folder, upload it to your Arduino in the Arduino IDE, and you're done — no hardware changes required.

Note: open firmware doesn't include the auto-update handshake, so Volumix won't push firmware updates to your hardware. You'll handle updates yourself via Arduino IDE — same workflow as any other Arduino project.

---

## Hardware Wiring (Nano DIY build)

If you're building your own Nano-based Faderbox or coming from a Deej setup, here's the standard pinout. **Volumix Faderbox owners can skip this section** — your hardware is pre-wired.

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

## Volumix Faderbox

A **Faderbox** is the hardware side of Volumix — a small box with 5 potentiometer sliders and 5 push buttons. The MCU inside talks to your PC over USB, and Volumix listens.

The Volumix Faderbox is the official hardware Volumix is designed around. It's a drop-in replacement for the original Nano build with a more capable MCU (ESP32-S3) that unlocks a bunch of features the Nano can't do.

<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/Midi_Controller_A-Camera_16.png" width="560" alt="Faderbox hardware">
</div>


### Native USB MIDI

The Volumix Faderbox shows up in your PC as a real MIDI device — same as any USB MIDI controller. No drivers, no LoopMIDI, no virtual ports. Your DAW, Voicemeeter, OBS, and any other MIDI-aware software see **"Volumix Faderbox"** directly in their MIDI input list.

- Each slider sends MIDI CC (channels 1–5 by default)
- MIDI mode is per-channel — mix audio sliders and MIDI sliders on the same device
- The hardware remembers which channels are in MIDI mode across reboots and PC swaps

<!-- IMAGE PLACEHOLDER: Screenshot of a DAW or Voicemeeter showing "Volumix Faderbox" in the MIDI input dropdown -->
<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-native-midi.png.jpg" width="560" alt="Volumix Faderbox listed as native MIDI device">
</div>

### MIDI buttons

When a channel is in MIDI mode, its mute button doubles as a **MIDI note** trigger with toggle behavior — first press = note-on, second press = note-off. Channels 1–5 use notes C4–E4 (60–64) on MIDI channel 1.

Perfect for DAW transport controls (play, record, loop), Voicemeeter macro buttons, OBS scene switching, or anything else triggered by a MIDI note.

### LED system

Each of the 5 sliders has an addressable RGB LED beside it. The Faderbox has three LED modes:

**Auto** — colors based on channel state:
- White when the channel has an app assigned and is playing
- Red when muted
- Green when in MIDI mode and the button is idle
- Pink when in MIDI mode and the button is toggled on
- Off when nothing is assigned

**Semi-auto** — same state logic, but you pick the colors yourself.

**Manual** — pick a static color per LED, ignoring channel state. In Manual mode you can also enable one of **7 animated effects**:
- **Solid** — your 5 colors stay put
- **Rainbow** — all LEDs cycle through hues together
- **Breathing** — each LED's color gently fades in and out
- **Wave** — rainbow flows across the strip
- **Comet** — single bright LED bounces back and forth
- **Chase** — LEDs light up sequentially
- **Twinkle** — random soft fade in and out per LED

Each effect has a **speed slider** (1–10) and a **global brightness** control. The Faderbox animates everything locally, so effects stay smooth even when Volumix isn't running.

A **"Flip MIDI LED state"** toggle is also available per channel — useful when downstream software (like Voicemeeter PTT) treats "button on" as "feature off" and you want the LED color to match what the software actually shows.

<!-- IMAGE PLACEHOLDER: GIF of the LED system in action — could show the three modes, or just the 7 effects cycling -->
<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-led-effects.gif" width="560" alt="LED effects on the Volumix Faderbox">
</div>

### Slider calibration

Every potentiometer has slightly different electrical limits — most don't reach the full 0V or 3.3V at the ends of their travel, leaving "dead zones" where the slider moves but the output doesn't change. The Volumix Faderbox includes a **step-by-step calibration wizard** that captures each slider's true minimum and maximum:

1. Open **Settings → Calibration**
2. Click **Start calibration**
3. Move slider 1 to the bottom → click **Capture min**
4. Move slider 1 to the top → click **Capture max**
5. Repeat for sliders 2–5

After calibration, you get clean 0–100% travel on every slider with no dead zones. Calibration is stored in firmware and survives reflashing the app, plugging into a different PC, or moving the device between machines.

<!-- IMAGE PLACEHOLDER: Screenshot of the Calibration wizard mid-flow with the live ADC bar and Capture button -->
<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-calibration.gif" width="560" alt="Calibration wizard">
</div>

### Pot direction flip (software)

If a slider moves the wrong way, flip it in **Settings → Channels** — no need to re-solder. The Faderbox remembers the direction settings on-device, so the inversion follows the hardware to any PC.

### Automatic firmware updates

Volumix detects when newer firmware is available for your Faderbox and updates it directly over USB — no Arduino IDE, no toolchain, nothing to install. The app:

1. Checks the bundled firmware version against what's currently on the device
2. If there's an update, shows a notification
3. One click → resets the chip into bootloader mode, flashes the new firmware, reboots
4. The Faderbox comes back online with the new firmware in about 15 seconds

If a flash fails (e.g. flaky USB cable), Volumix automatically retries — no need to recover manually.

<!-- IMAGE PLACEHOLDER: Screenshot of the firmware update notification or the in-progress flash dialog -->
<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-firmware-update.gif" width="560" alt="In-app firmware update">
</div>

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

<table align="center" width="720">
  <tr>
    <td width="160" align="center">
      <a href="https://discord.gg/eNYyHBM7cM"><img src="https://img.shields.io/badge/Discord-5865F2?logo=discord&logoColor=white&style=for-the-badge" alt="Discord" height="48"/></a>
    </td>
    <td>
      <strong>Join the Volumix Discord</strong><br/>
      Setup help, build showcases, feature requests, and chats with other Faderbox users.
    </td>
  </tr>
</table>

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

### Naming your sliders

Right-click any pill (the rounded button under each slider) → choose **Rename…** to give the channel a custom name. Useful when one slider controls multiple apps — instead of seeing "chrome +2" you can call it "Browsers."

To go back to the default app name, right-click → **Clear label**.

<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-naming-slider.gif" width="200" alt="Right-click rename menu">
</div>

### Controlling your microphone

Open the app picker on any slider and look for the **Input devices** section at the top. Every microphone or input device on your system shows up there alongside your apps. Pick one, and that slider now controls the mic's input level. The mute button hard-mutes the mic at the Windows level — every app that's listening hears silence instantly.

<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/input-device.png" width="300" alt="Input devices in app picker">
</div>

### Switching audio devices

If you switch your default output (e.g. plug in headphones), Volumix detects it and instantly re-applies your slider positions to the new device — so the audio matches what your Faderbox shows, every time. No more surprise loud blasts when Windows remembers the headphones were at 100% from yesterday.

<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/device-switch.svg" width="600" alt="Slider stays at 70% — audio matches across device switch">
</div>



---

## MIDI output

Volumix can send **MIDI Control Change** messages instead of (or alongside) controlling Windows audio. This lets your Faderbox drive any app that accepts MIDI input — Voicemeeter, OBS, Streamlabs, music DAWs (Reaper, Ableton, FL Studio), VTube Studio, Stream Deck, and more.

### Volumix Faderbox (native USB MIDI)

If you have the official Volumix Faderbox, MIDI works out of the box:

1. Open Volumix → **Settings → MIDI** → toggle the channels you want in MIDI mode
2. In your target app, pick **"Volumix Faderbox"** from the MIDI input list
3. Use **MIDI Learn**, move a Volumix slider, done

No virtual ports, no extra software, no setup. The Faderbox shows up alongside any other USB MIDI controller you might have.

### Nano DIY builds (via LoopMIDI)

The Nano doesn't have native MIDI, so it routes MIDI through Volumix using a free virtual port. We recommend **LoopMIDI** by Tobias Erichsen:

1. Download and install [LoopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html) (free)
2. Launch LoopMIDI, type a name (e.g. `volumix`) in the bottom box, click the **+** button to create the port
3. Open Volumix → **Settings → MIDI** → pick your new port from the dropdown
4. For each slider you want to use as MIDI, flip its toggle on — the slider turns **green** and shows `MIDI` inside the knob
5. In your target app, use **MIDI Learn**, then move the Volumix slider to bind it

By default each slider sends a different CC number (1–5). You can change these per channel in Settings → MIDI if your target app needs specific values.

### What it looks like

A MIDI-enabled slider has a green fill, a green-bordered knob with **MIDI** inside it, and the pill below shows `CC <number>` (or your custom label, if you've set one).

<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/midicontroll.gif" width="560" alt="Settings window">
</div>


### Voicemeeter Example

<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/midivoicemetertest.gif" width="1000" alt="Settings window">
</div>

---

## Settings


<div align="center">
  <img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/volumix-setting.gif" width="560" alt="Settings window">
</div>


| Setting | What it does |
|---------|--------------|
| **Auto-connect** | Reconnects to your Faderbox automatically on startup |
| **Start on system boot** | Launches Volumix when Windows starts (hidden in tray) |
| **Start minimized** | App starts in the tray instead of showing the window |
| **Dark mode** | Dark-themed UI |
| **Pot direction** | Flip individual sliders if they're wired backwards |
| **Calibration** *(Faderbox only)* | Step-by-step wizard to capture each slider's true min/max range |
| **MIDI output** | Send Control Change messages instead of controlling Windows audio (per-slider toggle) |
| **Lights** *(Faderbox only)* | LED mode, colors, brightness, effects, and per-channel flip toggles |
| **Check for updates** | Manually check GitHub for newer app and firmware versions |
| **Reset all settings** | Wipe everything and start over fresh |


---

## FAQ

**Do I need to install any drivers?**
No. Arduino Nanos with the standard CH340 chip are recognized by Windows 10/11 out of the box. The Volumix Faderbox uses native USB and doesn't need drivers either.

**Does Volumix work on Mac or Linux?**
Not yet. Volumix uses Windows-specific audio APIs (WASAPI). Cross-platform support isn't on the roadmap right now.

**Can I use fewer than 5 sliders?**
Yes. Unassigned sliders just do nothing. You can physically build a 2-slider or 3-slider Faderbox and the app will still work — the extra channels will just sit empty.

**Why does it take a second or two the first time I launch it?**
On first run, Volumix compiles a tiny helper program using your system's built-in C# compiler (no install needed — it ships with Windows). After that, it launches instantly.

**Can I use this with DaVinci Resolve / OBS / any specific app?**
If it shows up in the Windows Volume Mixer, it'll work with Volumix.

**Why does my volume sometimes jump when I plug in headphones?**
It shouldn't anymore — Volumix automatically re-applies your Faderbox positions whenever you switch output devices. There's a brief ~200ms window where Windows briefly uses its old per-device memory, but Volumix corrects it immediately.

**Can I rename a slider to show something other than the app name?**
Yes — right-click the app pill under the slider, choose Rename…, type your label (up to 20 characters), press Enter. Right-click → Clear label to revert.

**Does Volumix control my microphone?**
Yes. When you open the app picker, you'll see an "Input devices" section at the top with every microphone and input device on your system. Assign one to a slider and you'll control its input volume; the mute button hard-mutes the mic system-wide.

**Can I use Volumix with Voicemeeter / OBS / a DAW?**
Yes — turn on MIDI mode for any slider in **Settings → MIDI**. The slider stops controlling Windows audio and instead sends MIDI Control Change messages, which any MIDI-aware app can listen to. On the Volumix Faderbox this works natively. On a Nano build you'll need a free virtual MIDI port like [LoopMIDI](https://www.tobias-erichsen.de/software/loopmidi.html) — see the MIDI section above for the full setup.

**Do I need LoopMIDI for the Volumix Faderbox?**
No. The Volumix Faderbox is a native USB MIDI device — it shows up directly in your DAW/OBS/Voicemeeter MIDI input list. LoopMIDI is only needed for Nano DIY builds.

**What does calibration do?**
Most slider potentiometers don't perfectly hit 0V or 3.3V at their physical limits, leaving small dead zones at the top or bottom of travel. Calibration captures each slider's actual range so 0% and 100% line up exactly with the physical ends. The setting is stored in firmware, so it travels with the hardware. *(Volumix Faderbox only.)*

**How do firmware updates work?**
For the Volumix Faderbox, Volumix bundles the latest firmware with the app and detects when your hardware is running an older version. One click in Settings updates the firmware automatically over USB. For Nano DIY builds, you handle firmware updates yourself via Arduino IDE.

**My LoopMIDI port isn't showing up in Volumix.**
First try clicking **Refresh ports** in **Settings → MIDI**. If that doesn't work, restart your PC — Windows' MIDI subsystem occasionally caches its device list and a reboot forces it to re-register newly-created virtual ports.

**Does the LED system work without Volumix running?**
The LEDs reflect Volumix-driven state (mute/active/MIDI), so they need Volumix running for state-based modes (Auto, Semi-auto). **Manual mode and effects** keep running on the Faderbox even when Volumix is closed — once you set an effect, the firmware animates it locally.


---

## Support the project
<img src="https://raw.githubusercontent.com/ThePrintingPilot/volumix/refs/heads/main/images/TPP-Mono.png" width="85" align="right" />

If Volumix made your setup better, the best way to help is to:

- ⭐ **Star this repo** so other people find it
- 🐛 **Report bugs** in [Issues](https://github.com/ThePrintingPilot/volumix/issues)
- 💡 **Suggest features** — I'm open to ideas
<br/>

<div align="center">
  <p>Got a Faderbox question, build to show off, or feature idea?</p>
  <a href="https://discord.gg/eNYyHBM7cM"><img src="https://img.shields.io/badge/Join%20the%20Volumix%20Discord-5865F2?logo=discord&logoColor=white&style=for-the-badge" alt="Join the Volumix Discord" /></a>
</div>

---
