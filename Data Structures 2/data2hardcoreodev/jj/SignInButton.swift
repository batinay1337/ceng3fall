//
//  SignInButton.swift
//  CommunityPlatform
//
//  Created by Batınay Ünsel on 19.12.2022.
//

import SwiftUI

struct SignInButton: View {
  @State private var email: String = "root"
  @State private var password: String = "toor"
  
  @State private var isLoginValid: Bool = false
  @State private var shouldShowLoginAlert: Bool = false
  
  var body: some View {
    NavigationView {
      VStack(alignment: .center) {
        TextField("email", text: self.$email)
        TextField("password", text: self.$password)
        
        NavigationLink(destination: Mainpage(),
                       isActive: self.$isLoginValid) {
                /*
                 Here we put the content view of `NavigationLink`.
                 It could be any `View` even `Button` but in this
                 example we use a `Text` with `onTapGesture`.
                 */
                Text("Login")
                    .onTapGesture {
                    //determine login validity
                    let isLoginValid = self.email == "root" && self.password == "toor"
                    
                    //trigger logic
                    if isLoginValid {
                      self.isLoginValid = true //trigger NavigationLink
                    }
                    else {
                      self.shouldShowLoginAlert = true //trigger Alert
                    }
                }
        }
          
          
      }
      .navigationBarTitle("Login Screen")
      .alert(isPresented: $shouldShowLoginAlert) {
        Alert(title: Text("Email/Password incorrect"))
      }
    }
  }
}


struct SignInButton_Previews: PreviewProvider {
    static var previews: some View {
        SignInButton()
    }
}
