
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;

namespace base
{

struct DataProviderStateMachine_ : public msm::front::state_machine_def<DataProviderStateMachine_>
{
    // The list of FSM states
    struct Connected : public msm::front::state<>
    {
        // every (optional) entry/exit methods get the event passed.
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& ) {std::cout << "entering: State1" << std::endl;}
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) {std::cout << "leaving: State1" << std::endl;}
    };
    struct Closed : public msm::front::state<>
    {
        template <class Event,class FSM>
        void on_entry(Event const& ,FSM&) {std::cout << "entering: State2" << std::endl;}
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) {std::cout << "leaving: State2" << std::endl;}
    };

    // the initial state of the player SM. Must be defined
    typedef Connected initial_state;

    // transition actions
    struct State2ToState3
    {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
        {
            std::cout << "my_machine::State2ToState3" << std::endl;
        }
    };
    struct State3ToState4
    {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
        {
            std::cout << "my_machine::State3ToState4" << std::endl;
        }
    };

    // guard conditions
    struct always_true
    {
        template <class EVT,class FSM,class SourceState,class TargetState>
        bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
        {
            std::cout << "always_true" << std::endl;
            return true;
        }
    };
    struct always_false
    {
        template <class EVT,class FSM,class SourceState,class TargetState>
        bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
        {
            std::cout << "always_false" << std::endl;
            return true;
        }
    };

    typedef my_machine_ p; // makes transition table cleaner
    
    // Transition table for player
    struct transition_table : mpl::vector<
        //    Start     Event         Next      Action               Guard
        //  +---------+-------------+---------+---------------------+----------------------+
        Row < State1  , none        , State2                                               >,
        Row < State2  , none        , State3  , State2ToState3                             >,
        Row < State3  , none        , State4  , none                , always_false         >,
        //  +---------+-------------+---------+---------------------+----------------------+
        Row < State3  , none        , State4  , State3ToState4      , always_true          >,
        Row < State4  , event1      , State1                                               >
        //  +---------+-------------+---------+---------------------+----------------------+
    > {};

    // Replaces the default no-transition response.
    template <class FSM,class Event>
    void no_transition(Event const& e, FSM&,int state)
    {
        std::cout << "no transition from state " << state
            << " on event " << typeid(e).name() << std::endl;
    }
};

// Pick a back-end
typedef msm::back::state_machine<DataProviderStateMachine_> DataProviderStateMachine;

}
