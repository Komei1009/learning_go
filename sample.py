# 囲碁プログラム

from sys import stderr, stdout, stdin

cmd_list = [
    "protocol_version", "name", "version", "list_commands",
    "boardsize", "komi", "time_settings", "time_left",
    "clear_board", "genmove", "play", "undo",
    "gogui-play_sequence", "showboard", "quit"
]

# GUIからの呼び出し
def include(str, cmd):
    return str.find(cmd) >= 0

# コマンド結果の送信
def send(res_cmd):
    stdout.write("= " + res_cmd + "\n\n")
    stdout.flush()

# 碁盤情報の作成
def board_create():
    return

# gtpコマンドの呼び出し
def call_gtp():
    while 1:
        str = stdin.readline().rstrip("\r\n")
        if str == "":
            continue
        elif include(str, "name"):
            send("sample")
        elif include(str, "protocol_version"):
            send("1")
        elif include(str, "version"):
            send("0.1")
        elif include(str, "list_commands"):
            stdout.write("=")
            for cmd in cmd_list:
                stdout.write(cmd + "\n")
            send("")
        elif include(str, "boardsize"):
            stdout.write("?unknown_command\n\n")
        elif include(str, "genmove"):
            send("C5")
        elif include(str, "quit"):
            send("")
            break
        else:
            stdout.write("?unknown_command\n\n")

while(1):
    call_gtp()