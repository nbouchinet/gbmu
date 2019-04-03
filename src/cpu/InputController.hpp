#ifndef INPUTCONTROLLER_H
# define INPUTCONTROLLER_H

#include "src/Fwd.hpp"
#include "src/IReadWrite.hpp"
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_member.hpp>
#include <atomic>

class InputController : public IReadWrite {
	private:
		ComponentsContainer& _components;
		std::atomic<Byte> _rP1;  //0xFF00
		std::atomic<Byte> _joypad_state;

	private:
		friend class boost::serialization::access;
		template <class Archive> void load(Archive &ar, const unsigned int) {
			Byte joypad_state;
			Byte rP1;

			ar & rP1;
			ar & joypad_state;

			_rP1.store(rP1);
			_joypad_state.store(joypad_state);
		}
		template <class Archive> void save(Archive &ar, const unsigned int) const {
			ar & _rP1.load();
			ar & _joypad_state.load();
		}
		BOOST_SERIALIZATION_SPLIT_MEMBER()

	public:

		void write(Word addr, Byte val) override;
		Byte read(Word addr) const override;
		void key_pressed(int val);
		void key_released(int val);
		Byte get_joypad_state() const;

		InputController(ComponentsContainer& components);
		void reset();
};

#endif // INPUTCONTROLLER_H
