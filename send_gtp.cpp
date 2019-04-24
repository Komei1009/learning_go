// GTPで通信するだけのサンプル
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void send_gtp(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  vfprintf( stdout, fmt, ap );  // 標準出力に書き出す
  va_end(ap);
}

int main()
{
  char str[256];
  // stdoutをバッファリングしないように。GTPで通信に失敗するので。
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);  // stderrに書くとGoGuiに表示される。
  for (;;) {
    if ( fgets(str, 256, stdin)==NULL ) break;  // 標準入力から読む

    if      ( strstr(str,"boardsize")   ) {
      send_gtp("= \n\n");    // "boardsize 19" 19路盤
      //fprintf( stderr, "stderrに書くとgoguiに表示されます\n");
    }
    else if ( strstr(str,"clear_board") ) send_gtp("= \n\n");
    else if ( strstr(str,"name")        ) send_gtp("= my_test\n\n");
    else if ( strstr(str,"version")     ) send_gtp("= 0.0.1\n\n");
    else if ( strstr(str,"genmove w")   ) {
      //fprintf( stderr, "I'm thinking...%d\n",100);
      send_gtp("= D4\n\n");  // 自分の手を送る。この例では "D4" に打つ
    }
    else if ( strstr(str,"genmove b")   ) send_gtp("= R15\n\n");
    // 相手の手を受信 "play W D17" のように来る
    else if ( strstr(str,"play")        ) send_gtp("= \n\n");
    else {
      send_gtp("= \n\n");  // それ以外のコマンドにはOKを返す
    }
  }
  return 0;
}