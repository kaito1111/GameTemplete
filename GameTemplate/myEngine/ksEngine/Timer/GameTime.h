#include "Timer/Stopwatch.h"
#include <queue>

namespace ksEngine {
	class GameTime {
		GameTime() {

		};
		~GameTime() {

		};

	public:
		static GameTime& GetInstance() {
			static GameTime t;
			return t;
		}
		//1�t���[���̌o�ߎ��Ԃ��擾(�P�ʁE�b)�B
		const float GetFrameDeltaTime()const {
			return 1.0 / 30.0f;// m_frameDeltaTime;
		}
		void PushDeltaFrameTime(float deltaTime) {
			m_frameDeltaTimeQue.push_back(deltaTime);
			if (m_frameDeltaTimeQue.size() > 60) {
				float totalTime = 0.0f;
				for (auto time : m_frameDeltaTimeQue) {
					totalTime += time;
				}
				//���ϒl���Ƃ�B
				m_frameDeltaTime = min(1.0f / 30.0f, totalTime / m_frameDeltaTimeQue.size());
				m_frameDeltaTimeQue.pop_front();
			}
		}
	private:
		std::list<float> m_frameDeltaTimeQue;
		float m_frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ���
	};

	static GameTime& gameTime() {
		return GameTime::GetInstance();
	}
}