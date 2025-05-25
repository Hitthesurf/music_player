#include "char_input.h"
#include "threads/mock_char_queue.h"
#include <gmock/gmock.h>

using namespace ::application;
using namespace ::tests;

class CharInputTests : public testing::Test
{
public:
  CharInputTests() :
    m_char_input(m_char_queue)
  {
  }

protected:
  MockCharQueue m_char_queue{};
  CharInput m_char_input;
};

TEST_F(CharInputTests, calling_input_adds_char_to_mock_queue_in_isr_safe_way)
{
  // Given
  std::string text = "test\n";

  // When
  for (size_t i = 0; i < text.length(); i++)
  {
    m_char_input.Input(text.at(i));
  }

  // Then
  ASSERT_EQ(text.length(), m_char_queue.state.add_isr_call_count);
  ASSERT_TRUE(std::equal(text.begin(), text.end(), m_char_queue.state.add_isr_letter.begin()));
}
