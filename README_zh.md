# MWelcome

[English](https://github.com/mrmagic2020/MForceAchievements?tab=readme-ov-file#mforceachievements) | 中文

一个简单的可定制插件，用于欢迎您的玩家加入您的服务器。

## 安装

### 使用 Lip

`lip install github.com/mrmagic2020/MWelcome`

### 手动安装

1. 从 [releases page](https://github.com/mrmagic2020/MWelcome/releases/latest) 下载最新版本。

2. 解压 **MWelcome-windows-x64.zip**。

3. 将 **MWelcome** 文件夹移动至BDS根目录下的 **plugins** 文件夹。

## 使用方法

首次运行时，MWelcome 将在**plugins/MWelcome/config/**中生成一个**config.json**文件，它看起来像这样：

```jsonc
{
  // 配置文件的版本。请勿修改。
  "version": 2,
  
  // 当有玩家加入服务器时，是否向每个在线玩家发送欢迎信息。
  "send_to_all_players": false,

  // 要发送的欢迎信息类型。选项： "chat"、"tip"、"toast"。
  "type": "toast",

  // Toast的标题。仅在 "type" 设置为 "toast" 时使用。
  "toast_title": "§lWelcome to the §bServer§r§l!§r",

  // Toast的内容。仅在 "type" 设置为 "toast" 时使用。
  // 请注意，{} 是玩家姓名的占位符。
  "toast_content": "Enjoy your stay, §o§6{}§r!",

  // 聊天信息的内容。仅在 "type" 设置为 "chat" 或 "tip" 时使用。
  "msg_content": "§lWelcome to the §bServer§r, §o§6{}§r!"
}
```

> [!IMPORTANT]
> 您需要重新启动服务器才能使更改生效。 或者，管理员可以在游戏中运行 **"/mwelcome "** 并使用GUI编辑配置选项，这些选项将立即生效。

| 类型    | 图片                                                                                    |
|-------|---------------------------------------------------------------------------------------|
| toast | ![toast](https://github.com/mrmagic2020/MWelcome/blob/main/assets/toast.jpg?raw=true) |
| chat  | ![chat](https://github.com/mrmagic2020/MWelcome/blob/main/assets/chat.jpg?raw=true)   |
| tip   | ![tip](https://github.com/mrmagic2020/MWelcome/blob/main/assets/tip.jpg?raw=true)     |

## 贡献

通过创建Issue来提问。

接受 PR。

## 许可

CC0-1.0 © mrmagic202020
