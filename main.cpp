#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define GAME_TERMINATE -1

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *img = NULL;
ALLEGRO_BITMAP *image = NULL;
ALLEGRO_BITMAP *image2 = NULL;
ALLEGRO_BITMAP *image3 = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_KEYBOARD_STATE keyState ;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_TIMER *timer2 = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE *song1=NULL;
ALLEGRO_FONT *font = NULL;
ALLEGRO_FONT *font1 = NULL;
ALLEGRO_FONT *font2 = NULL;
ALLEGRO_FONT *font3 = NULL;



//Custom Definition
const char *title = "Final Project 106062231";
const float FPS = 60;
const int WIDTH = 800;
const int HEIGHT = 600;
int blood1,blood2,flage=0,flagl=0,magic1,magic2;
int runa,rund,runright,runleft;
typedef struct character
{
    double x;
    double y;
    ALLEGRO_BITMAP *image_path;

}Character;

Character character1;
Character character2;
Character character3;
Character character4;
Character hit_1;
Character hit_2;
Character bighit_1;
Character bighit_2;



int imageWidth = 0;
int imageHeight = 0;
int draw = 0;
int done = 0;
int window = 1;
double V1=-3,V2=-3,gravity=0.01;
int jump1_flag=0,jump2_flag=0;
bool judge_1_window = false;
bool judge_2_window = false;
bool judge_3_window = false;
bool judge_4_window = false;
bool ture_1 , ture_2;
int flagforwinniebig = 0;
int flagforwinniesmall=0;
int flagforpigletbig=0;
int flagforpigletsmall=0;

int countdown = 30;

void show_err_msg(int msg);
void game_init();
void game_begin();
int process_event();
int game_run();
void game_destroy();

int main() {
    int msg = 0;

    game_init();
    hit_1.x=900;
    hit_1.y=100000;
    hit_2.x=-100;
    hit_2.y=100000;
    bighit_1.x=900;
    bighit_1.y=100000;
    bighit_2.x=-100;
    bighit_2.y=100000;
    game_begin();


    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }

    game_destroy();
    return 0;
}
void run()
{
    if(runa==1&&character1.x>20) character1.x-=1;
    if(rund==1&&character1.x<320) character1.x+=1;
    if(runright==1&&character2.x<740) character2.x+=1;
    if(runleft==1&&character2.x>420) character2.x-=1;
}
void jump()
{
    if(jump1_flag==1)
    {
        al_draw_bitmap(character4.image_path, character1.x, character1.y, 0);
        character1.y+=V1;
        V1+=gravity;
        if(character1.y>=HEIGHT/2+75)
        {
            jump1_flag=0;
            V1=-3;
            character1.y=HEIGHT/2+74;
        }
    }
    if(jump2_flag==1)
    {

        al_draw_bitmap(character3.image_path, character2.x, character2.y, 0);
        character2.y+=V2;
        V2+=gravity;
        if(character2.y>=HEIGHT/2+60)
        {
            jump2_flag=0;
            V2=-3;
            character2.y=HEIGHT/2+59;
        }
    }

}
void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d\n", msg);
    game_destroy();
    exit(9);
}

bool firstforattack = true;
bool firstforattack2 = true;

void bar_throw1(){
    static double tpos,tdist;
    if(firstforattack == true){
        tpos = hit_1.x;
        tdist=character2.x-character1.x+50;
    }
    firstforattack = false;
    hit_1.x+=0.6;
    if(hit_1.x - tpos <=tdist/4 ) hit_1.y-=0.6;
    else if(hit_1.x - tpos > tdist/4 && hit_1.x - tpos <= tdist/4) hit_1.y-=0.5;
    else if(hit_1.x - tpos >2*tdist/4 && hit_1.x - tpos <= 3*tdist/4) hit_1.y+=0.5;
    else if(hit_1.x - tpos > tdist) hit_1.y+=0.6;
    al_draw_bitmap(hit_1.image_path, hit_1.x, hit_1.y, 0);
}
void bar_throw2(){
    static double tpos,tdist;
    if(firstforattack2 == true){
        tpos = hit_2.x;
        tdist=character2.x-character1.x+50;
    }
    firstforattack2 = false;
    hit_2.x-=0.6;
    if(tpos - hit_2.x <= tdist/4 ) hit_2.y-=0.6;
    else if(tpos - hit_2.x > tdist/4 && tpos - hit_2.x <= tdist/4) hit_2.y-=0.5;
    else if(tpos - hit_2.x >2*tdist/4 && tpos - hit_2.x <= 3*tdist/4) hit_2.y+=0.5;
    else if(tpos - hit_2.x > tdist) hit_2.y+=0.6;
    al_draw_bitmap(hit_2.image_path, hit_2.x, hit_2.y, 0);
    /*hit_2.x-=1;
    al_draw_bitmap(hit_2.image_path, hit_2.x, hit_2.y, 0);*/

}
void bigbar_throw1(){


    bighit_1.x+=1;
    al_draw_bitmap(bighit_1.image_path, bighit_1.x, bighit_1.y, 0);
    flage=0;

}
void bigbar_throw2(){

    bighit_2.x-=1;
    al_draw_bitmap(bighit_2.image_path, bighit_2.x, bighit_2.y, 0);
    flagl=0;

}

void game_init() {
    if (!al_init()) {
        show_err_msg(-1);
    }
    if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
        show_err_msg(-1);
    }
    if(!al_init_acodec_addon()){
        fprintf(stderr, "failed to initialize audio codecs!\n");
        show_err_msg(-1);
    }
    if (!al_reserve_samples(1)){
        fprintf(stderr, "failed to reserve samples!\n");
        show_err_msg(-1);
    }
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    event_queue = al_create_event_queue();
    if (display == NULL || event_queue == NULL) {
        show_err_msg(-1);
    }
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    hit_1.image_path = al_load_bitmap("honeyjar.png");
    hit_2.image_path = al_load_bitmap("honeyjar.png");
    bighit_1.image_path = al_load_bitmap("bighoneyjar.png");

    bighit_2.image_path = al_load_bitmap("bighoneyjar.png");

    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void game_begin() {
    // Load sound
    song = al_load_sample( "thepooh.WAV" );
    if (!song){
        printf( "Audio clip sample not loaded!\n" );
        show_err_msg(-1);
    }
    // Loop the song until the display closes
    al_play_sample(song, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    al_clear_to_color(al_map_rgb(100,100,100));
    // Load and draw text
    img = al_load_bitmap("menu.jpg");
    al_draw_bitmap(img, 0, 0, 0);

    if (img == NULL)

        show_err_msg(-1);
    font = al_load_ttf_font("pirulen.ttf",12,0);
    font1 = al_load_ttf_font("pirulen.ttf",30,0);
    font2 = al_load_ttf_font("pirulen.ttf",60,0);
    font3 = al_load_ttf_font("pirulen.ttf",24,0);

    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+20 , ALLEGRO_ALIGN_CENTRE, "Press 'alt' to 'How To Play'");
    al_draw_rectangle(200, 310, 600, 350, al_map_rgb(255, 255, 255), 0);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+120 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to Start");
    al_draw_rectangle(200, 410, 600, 450, al_map_rgb(255, 255, 255), 0);
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Esc' to Exit");

    al_flip_display();
}


int process_event(){
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    // Our setting for controlling animation
    if(event.timer.source == timer){
        ture_1 = !ture_1 ;
        if(countdown>0) countdown--;
    }
    if(event.timer.source == timer2){
        ture_2 = !ture_2 ;
        if(flagforwinniebig > 0) flagforwinniebig--;
        if(flagforwinniesmall > 0) flagforwinniesmall--;
        if(flagforpigletbig > 0) flagforpigletbig--;
        if(flagforpigletsmall > 0) flagforpigletsmall--;
    }

    // Keyboard
    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        switch(event.keyboard.keycode)
        {
            // P1 control


            case ALLEGRO_KEY_A:
                runa=1;
                break;
            case ALLEGRO_KEY_D:
                rund=1;
                break;
            case ALLEGRO_KEY_W:

                jump1_flag=1;
                break;

            // P2 control

            case ALLEGRO_KEY_RIGHT:
                runright=1;
                break;
            case ALLEGRO_KEY_LEFT:
                runleft=1;
                break;
            case ALLEGRO_KEY_UP:

                jump2_flag=1;
                break;
            case ALLEGRO_KEY_Q:
                hit_1.x=character1.x+30;
                hit_1.y=character1.y+20;
                firstforattack = true;
                break;
            case ALLEGRO_KEY_K:
                hit_2.x=character2.x+30;
                hit_2.y=character2.y+30;
                firstforattack2 = true;
                break;
            case ALLEGRO_KEY_E:
                if(magic1<340)
                {
                    flage=1;
                    bighit_1.x=character1.x+30;
                    bighit_1.y=character1.y+20;

                }
                break;

            case ALLEGRO_KEY_L:
                if(magic2<340)
                {
                  flagl=1;
                bighit_2.x=character2.x+30;
                bighit_2.y=character2.y+30;

                }
                 break;



            // For Start Menu
            case ALLEGRO_KEY_ENTER:

                judge_1_window = true;
                al_stop_samples();
                al_destroy_sample(song);
                song1=al_load_sample("smallworld.wav");
                if(!song1)
                {
                    printf("Audio 2 clip sample not loaded!\n");
                    show_err_msg(-1);
                }
                al_play_sample(song1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                break;
            case ALLEGRO_KEY_ALT:
                judge_2_window = true;
                break;



           case ALLEGRO_KEY_BACKSPACE:
               if(window==3)
                {
                    judge_1_window=false;
                    judge_2_window=false;
                    judge_3_window=false;
                    judge_4_window=false;
                    window=1;
                    game_begin();
                    break;
                }
                if(window==2)
                {
                    al_stop_samples();
                al_destroy_sample(song1);
                song=al_load_sample("thepooh.wav");
                if(!song)
                {
                    printf("Audio 2 clip sample not loaded!\n");
                    show_err_msg(-1);
                }
                al_play_sample(song1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                    window=1;
                    judge_1_window=false;
                    judge_2_window=false;
                    judge_3_window=false;
                    judge_4_window=false;

                    game_begin();
                    break;
                }
               else if(window==4)
                {
                    al_stop_samples();
                al_destroy_sample(song1);
                song=al_load_sample("thepooh.wav");
                if(!song)
                {
                    printf("Audio 2 clip sample not loaded!\n");
                    show_err_msg(-1);
                }
                al_play_sample(song1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                    window=1;
                    judge_1_window=false;
                    judge_2_window=false;
                    judge_3_window=false;
                    judge_4_window=false;
                    game_begin();
                    break;
                }
                else if(window==5)
                {
                    al_stop_samples();
                    al_destroy_sample(song1);
                    song=al_load_sample("thepooh.wav");
                if(!song)
                {
                    printf("Audio 2 clip sample not loaded!\n");
                    show_err_msg(-1);
                }
                al_play_sample(song1,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
                    window=1;
                    judge_1_window=false;
                    judge_2_window=false;
                    judge_3_window=false;
                    judge_4_window=false;
                    game_begin();
                    break;
                }





        }
    }
    if(event.type==ALLEGRO_EVENT_KEY_UP)
    {
        switch(event.keyboard.keycode)
        {
            // P1 control

             case ALLEGRO_KEY_W:

                jump1_flag=1;
                break;
            case ALLEGRO_KEY_A:
                runa=0;
                break;
            case ALLEGRO_KEY_D:
                rund=0;
                break;

            // P2 control

            case ALLEGRO_KEY_RIGHT:
                runright=0;
                break;
            case ALLEGRO_KEY_LEFT:
                runleft=0;
                break;



            // For Start Menu
            case ALLEGRO_KEY_ENTER:
                if(window==1) {
                        judge_1_window = true;
                }
                break;
            case ALLEGRO_KEY_ALT:
                judge_2_window = true;
                break;
            case ALLEGRO_KEY_E:
               // flage=0;
                break;
            case ALLEGRO_KEY_L:
                //flagl=0;
                break;


           case ALLEGRO_KEY_ESCAPE:
               if(window==1)
                return GAME_TERMINATE;
                break;




        }
    }

    // Shutdown our program
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;

    return 0;
}



int game_run() {
    int error = 0;
    // First window(Menu)
    if(window == 1){
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
            if(judge_1_window) {
                window = 2;
                blood1=0;
                blood2=0;
                magic1=0;
                magic2=0;
                countdown=30;


                // Setting Character
                character1.x = WIDTH / 2 - 300;
                character1.y = HEIGHT / 2 + 75;
                character2.x = WIDTH / 2 + 170;
                character2.y = HEIGHT / 2 + 60;
                character1.image_path = al_load_bitmap("pooh1.png");
                character2.image_path= al_load_bitmap("piglet-happy1.png");
                character3.image_path= al_load_bitmap("piglet-jump.png");
                character4.image_path= al_load_bitmap("pooh-happy.png");


                background = al_load_bitmap("stage.jpg");

                //Initialize Timer
                timer  = al_create_timer(1.0);
                timer2  = al_create_timer(1.0/2.0);
                al_register_event_source(event_queue, al_get_timer_event_source(timer)) ;
                al_register_event_source(event_queue, al_get_timer_event_source(timer2)) ;
                al_start_timer(timer);
                al_start_timer(timer2);


            }
            else if(judge_2_window)
            {
                window=3;
                background=al_load_bitmap("About.jpg");
            }
             else if(judge_3_window)
            {
                window=4;

            }
             else if(judge_4_window)
            {
                window=5;

            }


        }
    }
    // Second window(Main Game)
    else if(window == 2){
        // Change Image for animation

        al_draw_bitmap(background, 0,0, 0);
        if(jump1_flag==0)al_draw_bitmap(character1.image_path, character1.x, character1.y, 0);
        if(jump2_flag==0)al_draw_bitmap(character2.image_path, character2.x, character2.y, 0);



        al_draw_filled_rectangle(20, 20, 360, 40, al_map_rgb(102, 255, 89));
        al_draw_filled_rectangle(20+blood1, 20, 20, 40, al_map_rgb(230, 0, 0));
        al_draw_filled_rectangle(420, 20, 760, 40, al_map_rgb(102, 255, 89));
        al_draw_filled_rectangle(760-blood2, 20, 760, 40, al_map_rgb(230, 0, 0));
        al_draw_filled_rectangle(20, 50, 360, 70, al_map_rgb(0, 47, 167));
        al_draw_filled_rectangle(20+magic1, 50, 20, 70, al_map_rgb(0, 0, 0));
        al_draw_filled_rectangle(420, 50, 760, 70, al_map_rgb(0, 47, 167));
        al_draw_filled_rectangle(760-magic2, 50, 760, 70, al_map_rgb(0, 0, 0));
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Backspace' to quit");


            //if(ture_1) al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-200 , ALLEGRO_ALIGN_CENTRE, "9");;
            //if(!ture_1) al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-200 , ALLEGRO_ALIGN_CENTRE, "0");;

            if(flagforwinniebig>0) al_draw_text(font1, al_map_rgb(0,0,0), character2.x+70, character2.y-70 , ALLEGRO_ALIGN_CENTRE, "-80");
            if(flagforwinniesmall>0) al_draw_text(font1, al_map_rgb(0,0,0), character2.x+70, character2.y-70 , ALLEGRO_ALIGN_CENTRE, "-20");
            if(flagforpigletbig>0) al_draw_text(font1, al_map_rgb(0,0,0), character1.x+70, character1.y-70 , ALLEGRO_ALIGN_CENTRE, "-80");
            if(flagforpigletsmall>0) al_draw_text(font1, al_map_rgb(0,0,0), character1.x+70, character1.y-70 , ALLEGRO_ALIGN_CENTRE, "-20");


            if(countdown%10 == 9)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "9");
            else if(countdown%10 == 8)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "8");
            else if(countdown%10 == 7)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "7");
            else if(countdown%10 == 6)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "6");
            else if(countdown%10 == 5)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "5");
            else if(countdown%10 == 4)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "4");

            else if(countdown%10 == 3)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "3");
            else if(countdown%10 == 2)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "2");
            else if(countdown%10 == 1)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "1");
            else if(countdown%10 == 0)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "0");

            if(countdown/10 == 3)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2-30, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "3");
            else if(countdown/10 == 2)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2-30, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "2");
            else if(countdown/10 == 1)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2-30, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "1");
            else if(countdown/10 == 0)al_draw_text(font3, al_map_rgb(255,255,0), WIDTH/2-30, HEIGHT/2-250 , ALLEGRO_ALIGN_CENTRE, "0");




        if(flage==1&&magic1<340) magic1+=85;
        if(flagl==1&&magic2<340) magic2+=85;
        bar_throw1();
        bar_throw2();
        bigbar_throw1();
        bigbar_throw2();
        run();
        jump();

        if(hit_1.x<=character2.x+0&&hit_1.x>=character2.x-40&&character2.y-40<=hit_1.y&&hit_1.y<=character2.y+40&&blood2<340)
        {
            blood2+=20;
            flagforwinniesmall = 1;
            hit_1.x=900;
            hit_1.y=100000000;
        }

        if(hit_2.x<=character1.x+40&&hit_2.x>=character1.x-40&&character1.y-40<=hit_2.y&&hit_2.y<=character1.y+40&&blood1<340)
        {
            blood1+=20;
            flagforpigletsmall = 1;
            hit_2.x=-100;
            hit_2.y=100000000;
        }
        if(bighit_1.x<=character2.x+40&&bighit_1.x>=character2.x-40&&character2.y-40<=bighit_1.y&&bighit_1.y<=character2.y+40&&blood2<340)
        {
            blood2+=80;
            flagforwinniebig = 1;
            bighit_1.x=900;
            bighit_1.y=100000000;
            if(magic2>0)
            {
                magic2-=85;
            }

        }

        if(bighit_2.x<=character1.x+40&&bighit_2.x>=character1.x-40&&character1.y-40<=bighit_2.y&&bighit_2.y<=character1.y+40&&blood1<340)
        {
            blood1+=80;
            flagforpigletbig = 1;
            bighit_2.x=-100;
            bighit_2.y=100000000;
            if(magic1>0)
            {
                magic1-=85;
            }
        }

        if(blood1>=340)
        {
            window=4;
            judge_3_window=true;


            background=al_load_bitmap("gameover.jpg");
        }
         if(blood2>=340)
        {
            window=5;
            judge_4_window=true;

            background=al_load_bitmap("gameover.jpg");
        }
        if(countdown==0){
            hit_1.x=900;
            hit_1.y=100000000;
            hit_2.x=-100;
            hit_2.y=100000000;
            bighit_1.x=900;
            bighit_1.y=100000000;
            bighit_2.x=-100;
            bighit_2.y=100000000;
            if(blood1>=blood2)
            {
                window=4;
                judge_3_window=true;

                background=al_load_bitmap("gameover.jpg");
            }
            else if(blood2>blood1)
            {
                window=5;
                judge_4_window=true;

                background=al_load_bitmap("gameover.jpg");
            }


            }








        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

        // Listening for new event
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }
    }

    else if(window==3){
        al_draw_bitmap(background, 0,0, 0);
        al_draw_text(font1, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-200 , ALLEGRO_ALIGN_CENTRE, "How To Play");
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-160 , ALLEGRO_ALIGN_CENTRE, "<You have four chances to throw the larger honey bar.>");
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-120 , ALLEGRO_ALIGN_CENTRE, "<If you are too near the honey bar,you will lose your blood.>");
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-80 , ALLEGRO_ALIGN_CENTRE, "<If you are hit by the honey bar,you will lose your blood.>");
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2-40 , ALLEGRO_ALIGN_CENTRE, "<However,if you are too near the honey bar,you will add your power.>");
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "<However,if you are hit by the honey bar,you will add your power.>");
        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+40 , ALLEGRO_ALIGN_CENTRE, "<When one player lose his/her all blood,the game will end.>");


        al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Backspace' to main menu");
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        if(!al_is_event_queue_empty(event_queue))
        {
            error=process_event();
        }
    }
     else if(window==4){
        al_draw_bitmap(background, 0,0, 0);
        if(blood2 < blood1||blood1>=340)
        {al_draw_text(font1, al_map_rgb(255,133,16), WIDTH/2, HEIGHT/2-200 , ALLEGRO_ALIGN_CENTRE, "GAME OVER");
        al_draw_text(font2, al_map_rgb(255,133,16),200 ,400 , ALLEGRO_ALIGN_CENTRE, "LOSER!!");
        al_draw_text(font2, al_map_rgb(255,133,16), 600, 400, ALLEGRO_ALIGN_CENTRE, "WINNER!!");
        al_draw_text(font, al_map_rgb(255,133,16), WIDTH/2, 550, ALLEGRO_ALIGN_CENTRE, "Press 'backspace' to return");
        }
        else if(blood2==blood1)
        {
        al_draw_text(font2, al_map_rgb(255,133,16), WIDTH/2, HEIGHT/2-200 , ALLEGRO_ALIGN_CENTRE, "Time's up!");
        al_draw_text(font2, al_map_rgb(255,133,16), WIDTH/2, HEIGHT/2 , ALLEGRO_ALIGN_CENTRE, "TIE!!");
        al_draw_text(font, al_map_rgb(255,133,16), WIDTH/2, 550, ALLEGRO_ALIGN_CENTRE, "Press 'backspace' to return");
        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        if(!al_is_event_queue_empty(event_queue))
        {
            error=process_event();
        }
    }
    else if(window==5){
        if(blood2 > blood1||blood2>=340)
        {al_draw_bitmap(background, 0,0, 0);
        al_draw_text(font1, al_map_rgb(255,133,16), WIDTH/2, HEIGHT/2-200 , ALLEGRO_ALIGN_CENTRE, "GAME OVER");
        al_draw_text(font2, al_map_rgb(255,133,16),200 ,400 , ALLEGRO_ALIGN_CENTRE, "WINNER!!");
        al_draw_text(font2, al_map_rgb(255,133,16), 600, 400, ALLEGRO_ALIGN_CENTRE, "LOSER!!");
        al_draw_text(font, al_map_rgb(255,133,16), WIDTH/2, 550, ALLEGRO_ALIGN_CENTRE, "Press 'backspace' to return");

        }
        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));
        if(!al_is_event_queue_empty(event_queue))
        {
            error=process_event();
        }
    }
            return error;




}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_timer(timer2);
    al_destroy_bitmap(image);
    al_destroy_sample(song);
    al_destroy_sample(song1);
}

