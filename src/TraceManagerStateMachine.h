
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>

#include <StateMachine.h>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;


struct TraceManagerSM_ : public msm::front::state_machine_def<TraceManagerSM_>
{
    // The list of FSM states
    struct Idle : public msm::front::state<>
    {
        // every (optional) entry/exit methods get the event passed.
        template <class Event,class FSM>
        void on_entry(Event const&,FSM& ) {std::cout << "Trace manager entering: Idle" << std::endl;}
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) {std::cout << "Trace manager leaving: Idle" << std::endl;}
    };
    struct Connected : public msm::front::state<>
    {
        template <class Event,class FSM>
        void on_entry(Event const& ,FSM&) {std::cout << "Trace manager entering: Connected" << std::endl;}
        template <class Event,class FSM>
        void on_exit(Event const&,FSM& ) {std::cout << "Trace manager leaving: Connected" << std::endl;}
    };

    // the initial state of the player SM. Must be defined
    typedef Idle initial_state;

    // transition actions
    struct RegisterHandler
    {
        template <class EVT,class FSM,class SourceState,class TargetState>
        void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
        {
            std::cout << "process register request" << std::endl;
        }
    };

    // Transition table for tracemanager
    struct transition_table : mpl::vector<
        //             Start                  Event                    Next                   Action               Guard
        //  +-----------------------+-----------------------+------------------------+---------------------+----------------------+
        Row < Idle                  ,        Register       ,       Connected        , RegisterHandler                            >
    > {};

};

// Pick a back-end
typedef msm::back::state_machine<TraceManagerSM_> TraceManagerSM;

class TraceManagerStateMachine : public StateMachine {
    public:
        void processEvent(Register event)
        {
            sm.process_event(event);
        }
    private:
        TraceManagerSM sm;
};

