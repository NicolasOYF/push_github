#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

//event define
struct EvStartBrewing{};
struct EvGrindBeans{};
struct EvHeatWater{};
struct EvBrewCoffee{};
struct EvCoffeeDone{};
struct EvStop{};
struct EvInterruptBrewing{};
struct EvBrewingError{};

struct CoffeeMachine : msm::front::state_machine_def<CoffeeMachine>{
    struct InitState : msm::front::state<>{
        template<class Event, class FSM>
        void on_entry(Event const&, FSM& ){
            std::cout<<"Entering: InitState state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting: InitState state"<<std::endl;
        }
    };

    struct StartBrewing : msm::front::state<>{
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Entering : StartBrewing state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting: StartBrewing state"<<std::endl;
        }
    };

    struct GrindBeans : msm::front::state<>{
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Entering GrindBean state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"exit GrindBeans state"<<std::endl;
        }
    };

    struct HeatWater : msm::front::state<>{
        template<class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Entering HeatWater state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting HeatWater state"<<std::endl;
        }
    };

    struct BrewCoffee : msm::front::state<>{
        template<class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Entering BrewCoffee State. "<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting BrewCoffee state."<<std::endl;
        }
    };

    struct CoffeeDone : msm::front::state<>{
        template<class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Entering CoffeeDone state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting CoffeeDone state"<<std::endl;
        }
    };

    struct Stop : msm::front::state<>{
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Entering Stop state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting Stop state"<<std::endl;
        }
    };

    struct InterruptBrewing : msm::front::state<>{
        template<class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Enterign InterruptBrewing state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting InterruptBrewing state"<<std::endl;
        }
    };

    struct BrewingError : msm::front::state<>{
        template<class Event, class FSM>
        void on_entry(Event const&, FSM&){
            std::cout<<"Entering BrewingError state"<<std::endl;
        }

        template<class Event, class FSM>
        void on_exit(Event const&, FSM&){
            std::cout<<"Exiting BrewingError state"<<std::endl;
        }
    };


typedef InitState initial_state;

//状态转换表
#define DO_NOTHING msm::front::none
struct transition_table : mpl::vector<
//state         event           next state      action      guard
msm::front::Row<InitState, EvStartBrewing, StartBrewing, DO_NOTHING, DO_NOTHING>,
msm::front::Row<StartBrewing, EvGrindBeans, GrindBeans, DO_NOTHING, DO_NOTHING>,
msm::front::Row<GrindBeans, EvHeatWater, HeatWater, DO_NOTHING, DO_NOTHING>,
msm::front::Row<HeatWater, EvBrewCoffee, BrewCoffee, DO_NOTHING, DO_NOTHING>,
msm::front::Row<BrewCoffee, EvCoffeeDone, CoffeeDone, DO_NOTHING, DO_NOTHING>,
msm::front::Row<CoffeeDone, EvStop, Stop, DO_NOTHING, DO_NOTHING>,
msm::front::Row<Stop, EvStop, InitState, DO_NOTHING, DO_NOTHING>,
msm::front::Row<BrewCoffee, EvInterruptBrewing, InterruptBrewing, DO_NOTHING, DO_NOTHING>,
msm::front::Row<BrewCoffee, EvBrewingError, BrewingError, DO_NOTHING, DO_NOTHING>,
msm::front::Row<InterruptBrewing, EvStop, Stop, DO_NOTHING, DO_NOTHING>,
msm::front::Row<BrewingError, EvStop, Stop, DO_NOTHING, DO_NOTHING> > {};

//未处理事件的日志
template<class FSM, class Event>
void no_transition(Event const& e, FSM&, int state){
    std::cout<<"NO Transition from state"<<state<<"on event "<<typeid(e).name()<<std::endl;
}

};

typedef msm::back::state_machine<CoffeeMachine> CoffeeStateMachine;



int main(int, char**){
    std::cout << "Hello, from boos_msm!\n";

    CoffeeStateMachine hsm;
    hsm.start();
    std::cout<<"CoffeeStateMachine started"<<std::endl;

    std::cout<<"Triggering EvStartingBrewing."<<std::endl;
    hsm.process_event(EvStartBrewing());

    std::cout<<"Triggering EvGrindBeans."<<std::endl;
    hsm.process_event(EvGrindBeans());

    std::cout<<"Triggering EvHeatWater. "<<std::endl;
    hsm.process_event(EvHeatWater());

    std::cout<<"Triggering EvBrewCoffee."<<std::endl;
    hsm.process_event(EvBrewCoffee());

    std::cout<<"Triggering EvCoffeeDone"<<std::endl;
    hsm.process_event(EvCoffeeDone());

    std::cout<<"Triggering EvStop. "<<std::endl;
    hsm.process_event(EvStop());

    std::cout<<"CoffeeStateMachine end."<<std::endl;
    
    return 0;
}
