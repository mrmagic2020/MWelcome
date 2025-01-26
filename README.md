# MWelcome

A simple customizable plugin to welcome your fellow players to your server.

## Installation

### Using Lip

`lip install github.com/mrmagic2020/MWelcome`

### Manual Installation

1. Download the latest release from the [releases page](https://github.com/mrmagic2020/MWelcome/releases/latest).

2. Unpack **MWelcome-windows-x64.zip**.

3. Move the **MWelcome** folder to the **plugins** folder under your BDS root directory.

## Usage

Upon first run, MWelcome will generate a **config.json** file in **plugins/MWelcome/config/**, which will look like this:

```jsonc
{
  // The version of the config file. Do NOT modify.
  "version": 2,
  
    // Whether to send the welcome message to every online player when a player joins the server.
  "send_to_all_players": false,

  // The type of welcome message to send. Options: "chat", "tip", "toast".
  "type": "toast",

  // The title of the toast message. Only used if "type" is set to "toast".
  "toast_title": "§lWelcome to the §bServer§r§l!§r",

  // The content of the toast message. Only used if "type" is set to "toast".
  // Note that {} acts as a placeholder for the player's name.
  "toast_content": "Enjoy your stay, §o§6{}§r!",

  // The content of the chat message. Only used if "type" is set to "chat" or "tip".
  "msg_content": "§lWelcome to the §bServer§r, §o§6{}§r!"
}
```

> [!IMPORTANT]
> You will need to restart your server for the changes to take effect. Alternatively, admins can run **"/mwelcome"** in-game and use the GUI to edit the configuration options, which will take effect immediately.

| Type  | Image                                                                                 |
| ----- | ------------------------------------------------------------------------------------- |
| toast | ![toast](https://github.com/mrmagic2020/MWelcome/blob/main/assets/toast.jpg?raw=true) |
| chat  | ![chat](https://github.com/mrmagic2020/MWelcome/blob/main/assets/chat.jpg?raw=true)   |
| tip   | ![tip](https://github.com/mrmagic2020/MWelcome/blob/main/assets/tip.jpg?raw=true)     |

## Contributing

Ask questions by creating an issue.

PRs accepted.

## License

CC0-1.0 © mrmagic202020
