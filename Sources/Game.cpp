#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
bool    cannonflag = true; //!< 砲台の上下判定 (C HW16A108 相馬)


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    PlayBGM("bgm_maoudamashii_8bit07.mp3");  //(G)hw15a139,中西
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-310, -150);//(A HW16A108 相馬　砲台を左に)
    targetRect = Rect(280, -140, 40, 40);//(A HW16A108 相馬　ターゲットを右に)
    bulletPos.x = -999;
    score = 0;
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
    }

    void PlaySE();  //(H)hw15a139 中西
    
    if(Input::GetKeyDown(KeyMask::Space)) {
        PlayBGM("se_maoudamashii_explosion03.mp3");
    }
    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 200 * Time::deltaTime;  //D:弾のスピードを上げる(HW16A113 多田 亮太)
        if (bulletPos.x > 320) {               //D:弾が画面右端を通り越したら再度発射可能にする(HW16A113 多田 亮太)
            bulletPos.x = -999;                //D:弾が画面右端を通り越したら再度発射可能にする(HW16A113 多田 亮太)
        }

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算   E:スコアを100点ずつ加算(HW16A113 多田 亮太)
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    
    cloudPos[0]+= 10.0f * Time::deltaTime*15;//(B HW16A108 相馬)
    //雲の移動(B HW16A108 相馬)
    if (cloudPos[0] > 300) {//(B HW16A108 相馬)
        cloudPos[0] = -558;                //(B HW16A108 相馬)
    }

    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    
    if (cannonPos.y <= -140) cannonflag = true;  //(C HW16A108 相馬)
    if (cannonPos.y > -70) cannonflag = false;   //(C HW16A108 相馬)
    if (cannonflag == true) cannonPos.y+=1;      //(C HW16A108 相馬)
    else cannonPos.y-=1;                         //(C HW16A108 相馬)

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 100.0f);    //E:スコアを大きくする(HW16A113 多田 亮太)
    DrawText(FormatString("%05d", score), Vector2(-319, 159), Color::black);  //E:スコアを下に下げる(HW16A113 多田 亮太) F:スコアを5桁の表示に変更(HW16A113 多田 亮太)
    DrawText(FormatString("%05d", score), Vector2(-320, 160), Color::white);  //E:スコアを下に下げる(HW16A113 多田 亮太) F:スコアを5桁の表示に変更(HW16A113 多田 亮太)
}
