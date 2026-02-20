#include "SDN.hh"

namespace {
  using transitions = std::array<std::array<States, 128>, (size_t) States::NUMBER_STATES>;
  using acceptings = std::array<bool, (size_t) States::NUMBER_STATES>;
  
  constexpr transitions build_transitions() {
    transitions transitions_table = {};
    
    for (size_t i = 0; i < (size_t) States::NUMBER_STATES; i++) {
      for (size_t j = 0; j < 128; j++) {
        transitions_table[i][j] = States::UNKNOWN;
      }
    }
    
    for (size_t i = (size_t) 'A'; i <= (size_t) 'Z'; i++) {
      transitions_table[(size_t) States::CHAR_START][i] = States::CHAR_BODY;
      transitions_table[(size_t) States::STRING_START][i] = States::STRING_BODY;
      transitions_table[(size_t) States::STRING_BODY][i] = States::STRING_BODY;
      
      transitions_table[(size_t) States::START][(size_t) i] = States::IDENTIFIER;
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    for (size_t i = (size_t) 'a'; i <= (size_t) 'z'; i++) {
      transitions_table[(size_t) States::CHAR_START][i] = States::CHAR_BODY;
      transitions_table[(size_t) States::STRING_START][i] = States::STRING_BODY;
      transitions_table[(size_t) States::STRING_BODY][i] = States::STRING_BODY;
      
      transitions_table[(size_t) States::START][(size_t) i] = States::IDENTIFIER;
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    for (size_t i = (size_t) '0'; i <= (size_t) '9'; i++) {
      transitions_table[(size_t) States::START][i] = States::INTEGER;
      transitions_table[(size_t) States::INTEGER][i] = States::INTEGER;
      
      transitions_table[(size_t) States::STRING_START][i] = States::STRING_BODY;
      transitions_table[(size_t) States::STRING_BODY][i] = States::STRING_BODY;
      
      transitions_table[(size_t) States::IDENTIFIER][(size_t) i] = States::IDENTIFIER;
    }
    
    transitions_table[(size_t) States::START][(size_t) '_'] = States::IDENTIFIER;
    transitions_table[(size_t) States::IDENTIFIER]['_'] = States::IDENTIFIER;
    
    transitions_table[(size_t) States::START][(size_t) '\''] = States::CHAR_START;
    transitions_table[(size_t) States::START][(size_t) '\"'] = States::STRING_START;
    transitions_table[(size_t) States::CHAR_BODY][(size_t) '\''] = States::CHAR_END;
    transitions_table[(size_t) States::STRING_BODY][(size_t) '\"'] = States::STRING_END;
    
    transitions_table[(size_t) States::START][(size_t) '('] = States::LEFT_PARENTHESIS;
    transitions_table[(size_t) States::START][(size_t) ')'] = States::RIGHT_PARENTHESIS;
    transitions_table[(size_t) States::START][(size_t) '['] = States::LEFT_BRACKET;
    transitions_table[(size_t) States::START][(size_t) ']'] = States::RIGHT_BRACKET;
    transitions_table[(size_t) States::START][(size_t) '{'] = States::LEFT_BRACE;
    transitions_table[(size_t) States::START][(size_t) '}'] = States::RIGHT_BRACE;
    transitions_table[(size_t) States::START][(size_t) ','] = States::COMMA;
    
    transitions_table[(size_t) States::START][(size_t) ':'] = States::COLON;
    transitions_table[(size_t) States::START][(size_t) '.'] = States::DECIMAL;
    
    transitions_table[(size_t) States::START][(size_t) '\n'] = States::NEWLINE;
    transitions_table[(size_t) States::START][(size_t) '\t'] = States::WHITESPACE;
    transitions_table[(size_t) States::START][(size_t) '\r'] = States::WHITESPACE;
    transitions_table[(size_t) States::START][(size_t) ' '] = States::WHITESPACE;
    transitions_table[(size_t) States::WHITESPACE][(size_t) '\t'] = States::WHITESPACE;
    transitions_table[(size_t) States::WHITESPACE][(size_t) '\r'] = States::WHITESPACE;
    transitions_table[(size_t) States::WHITESPACE][(size_t) ' '] = States::WHITESPACE;
    
    return transitions_table;
  }
  
  constexpr acceptings build_acceptings() {
    acceptings acceptings_table = {};
    
    for (size_t i = 0; i < (size_t) States::NUMBER_STATES; i++) {
      acceptings_table[i] = false;
    }
    
    acceptings_table[(size_t) States::NEWLINE] = true;
    acceptings_table[(size_t) States::WHITESPACE] = true;
    
    acceptings_table[(size_t) States::IDENTIFIER] = true;
    acceptings_table[(size_t) States::INTEGER] = true;
    acceptings_table[(size_t) States::STRING_END] = true;
    acceptings_table[(size_t) States::CHAR_END] = true;
    
    acceptings_table[(size_t) States::LEFT_PARENTHESIS] = true;
    acceptings_table[(size_t) States::RIGHT_PARENTHESIS] = true;
    acceptings_table[(size_t) States::LEFT_BRACKET] = true;
    acceptings_table[(size_t) States::RIGHT_BRACKET] = true;
    acceptings_table[(size_t) States::LEFT_BRACE] = true;
    acceptings_table[(size_t) States::RIGHT_BRACE] = true;
    acceptings_table[(size_t) States::COMMA] = true;
    
    acceptings_table[(size_t) States::COLON] = true;
    acceptings_table[(size_t) States::DECIMAL] = true;
    
    return acceptings_table;
  }
}

std::vector<Token> SDN::Lexer::tokenize() {
  static constexpr transitions transition_table = build_transitions();
  static constexpr acceptings acceptings_table = build_acceptings();
  std::vector<Token> tokens = {};
  
  for (int i = 0; i < source.size(); i++) {
    current = source[i];
    state = transition_table[(size_t) last_state][(unsigned char) current];
    
    if (state == States::UNKNOWN && acceptings_table[(size_t) last_state]) {
      if (!handle_whitespace()) {
        lexeme = source.substr(start_position, i - start_position);
        tokens.push_back(Token(last_state, lexeme));
      }
      
      last_state = States::START;
      start_position = i;
      i--;
    } else if (state == States::UNKNOWN) {
      std::cerr << "ERROR: Unknown token at line " << line_number << ".\n";
      std::exit(1);
    } else {
      last_state = state;
    }
  }
  
  // Final token flush
  if (acceptings_table[(size_t) last_state]) {
    if (!handle_whitespace())
      tokens.push_back(Token(last_state, lexeme));
  }
  
  return tokens;
}

bool SDN::Lexer::handle_whitespace() {
  switch ((size_t) last_state) {
    case (size_t) States::NEWLINE:
      line_number++;
      return true;
    case (size_t) States::WHITESPACE:
      return true;
    default:
      return false;
  }
}
