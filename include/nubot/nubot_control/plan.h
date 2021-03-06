#ifndef PLAN_H
#define PLAN_H

#include <cmath>
#include "core.hpp"
#include "nubot/nubot_control/subtargets.h"
#include "nubot/nubot_control/behaviour.hpp"
#include "nubot/nubot_control/world_model_info.h"

using namespace std;
namespace nubot
{
        class Plan
        {
        public:
                Plan();

                /***********catch ball***********/
                void catchBall();
                void catchBallForCoop();
                void catchBallSlowly();
                void catchMovingBall();
                void catchMotionlessBall();
                void Get_Ball_Mode(int state);
                

                /***********postion*************/
                void positionAvoidObs(DPoint target, float theta, float stopdis, float stoptheta);
                void driblleControl(DPoint target, double acc, double sacc, double lvel, double maxvel);
                // void move2Positionwithobs(DPoint target);  // move to the target point with obstacles avoidance
                void move2Positionwithobs_noball(DPoint target, float maxvel, float maxacc, bool avoid_ball = false);

                /***********PE and PO***********/
                double PECrossBackMIdlleLine(double direction);
                double PEOutField(double direction);
                double PEInOurPenaty(double direction);
                double PObleDirection4OurField(double direction, double predictlen, double cobledirection, double kobledirection);
                double PObleDirection(double direction, double predictlen, double cobledirection, double kobledirection);

                /***********check***********/
                bool IsNullInTrap(double direction, double swidth, double lwidth, double len);
                /*********find and search*********/
                double FindBstDirectionForAvoid();
                double FindBstDirectionForAvoid2(DPoint target);
                int GetAvoidState();
                double SearchDirectionforMinPEPoint(double oridirection, double step, int lefttime, int righttime);
                bool SearchMinPE4PassThroughforOurField(double &direction, double pridictlen, DPoint trap[4], double step, int flg);
                bool SearchMinPE4PassThrough(double &direction, double pridictlen, DPoint trap[4], double step, int flg);
                void update();

        public:
                World_Model_Info *world_model_;
                Behaviour m_behaviour_;
                Subtargets m_subtargets_;

                float kp;
                float kalpha;
                float kbeta;
                bool inourfield_;
                bool inoppfield_;
                double lastdirection;

                DPoint robot_pos_;
                Angle robot_ori_;
                DPoint robot_vec_;
                DPoint ball_pos_;
                DPoint ball_vel_;
                vector<DPoint> target_;

        public:
                bool isinposition_;
                // add
                nubot_common::ActionCmd *action;
                DPoint startPoint;
                bool PassBall_Action(int catch_ID, int pass_mode_);
                void CatchPassedBall(void);
                void ProtectBallTry();
                const DPoint get_fly_landing_point()

                bool defend_occupied[5];
                bool attack_occupied[5];
                void attack(); //??????
                void defend(); //??????

                //???????????????private

                //void mark(); //??????
                //?????? ?????????????????????????????????
                void block();
                //????????????
                void defend_shoot(); 
                //????????????
                void blockPassingBall();
                //1v1 ????????????????????????????????????
                void defend1v1(); 
                //??????
                void mark();
                //??????
                bool moveBall(DPoint);
                bool isMoving = false;
                //shoot
                void shoot_1(bool&);
                int canPass(int);
        private:
                const double DEG2RAD = 0.01745329251994329547;
                const int RUN = 1;
                const int FLY = -1;
                const double MAX = 2147483647.0; 
                const double MIN = -2147483647.0;
        private:

                //??????????????????
                int nearest_point(DPoint);

                //defend
                //?????????????????????????????????????????????
                int nearest_oppdribble();     
                //???????????????
                bool ball_is_free();
                //??????????????????
                int oppDribble();
                //???????????????????????????????????????        
                int opp_nearestToOurGoal();
                //???????????????????????????????????????
                int numofinOurPenalty();
                //???????????????????????????????????????????????????
                int Snd_nearest_oppdribble();
                //???????????????????????????????????????
                int opp_getsforward();
                //???????????????????????????????????????
                int nearest_opp();
                //defend end
        };
}
#endif // PLAN_H
